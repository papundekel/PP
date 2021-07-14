#pragma once
#include <memory>
#include <type_traits>

#include "apply_template.hpp"
#include "apply_transform.hpp"
#include "concepts/reference.hpp"
#include "conditional.hpp"
#include "construct_pack.hpp"
#include "copy_cvref.hpp"
#include "decompose_template.hpp"
#include "empty.hpp"
#include "empty_iterator.hpp"
#include "get_value.hpp"
#include "id.hpp"
#include "remove_cvref.hpp"
#include "remove_pointer.hpp"
#include "size_t.hpp"
#include "transform_view.hpp"
#include "tuple.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, typename Tag>
		class array_wrap_wrap : public forward_wrap<T>
		{
		public:
			constexpr array_wrap_wrap(T&& arg, Tag)
				: forward_wrap<T>(PP_FORWARD(arg))
			{}
		};
		template <typename T, typename Tag>
		array_wrap_wrap(T&&, Tag) -> array_wrap_wrap<T, Tag>;
	}

	template <typename, size_t>
	class array;
	template <typename, typename>
	struct array_iterator;
	template <typename>
	struct array_iterator_transform;

	namespace detail
	{
		class array_helper;

		template <typename T>
		class array_wrap
		{
			template <typename, size_t>
			friend class PP::array;
			template <typename, size_t>
			friend class array_impl;
			template <typename, typename>
			friend class PP::array_iterator;
			template <typename>
			friend class PP::array_iterator_transform;

			T obj;

			array_wrap() = default;

			template <typename U>
			constexpr array_wrap(array_wrap_wrap<U, placeholder_t> arg)
				: obj(arg--)
			{}
			template <typename U>
			constexpr array_wrap(array_wrap_wrap<U, in_place_t> i)
				: obj(i--())
			{}
		};

		template <typename T, size_t C>
		class array_impl
		{
			friend array<T, C>;
			friend array_helper;

			array_wrap<T> buffer[C];

			array_impl() = default;

			constexpr array_impl(auto tag, auto&&... args) noexcept
				: buffer(array_wrap_wrap{PP_FORWARD(args), tag}...)
			{}
		};
		template <typename T>
		class array_impl<T, 0>
		{
		protected:
			constexpr array_impl(auto) noexcept
			{}
		};
	}

	template <typename T, size_t C>
	class array : private detail::array_impl<T, C>
	{
		friend detail::array_helper;

		static constexpr auto non_reference_type = !concepts::reference<T>;

	public:
		array() = default;

		constexpr array(auto tag,
						concepts::type auto,
						auto&&... args) requires(sizeof...(args) == C)
			: detail::array_impl<T, C>(tag, PP_FORWARD(args)...)
		{}

		constexpr auto element(concepts::value auto) const noexcept
		{
			return PP::type<T>;
		}
		constexpr auto tuple_count() const noexcept
		{
			return PP::value<C>;
		}
		constexpr auto&& operator[](size_t i) &;
		constexpr auto&& operator[](size_t i) const&;
		constexpr auto&& operator[](size_t i) &&;
		constexpr auto&& operator[](size_t i) const&&;
		constexpr auto&& operator[](concepts::value auto i) &
		{
			return (*this)[*i];
		}
		constexpr auto&& operator[](concepts::value auto i) const&
		{
			return (*this)[*i];
		}
		constexpr auto&& operator[](concepts::value auto i) &&
		{
			return move(*this)[*i];
		}
		constexpr auto&& operator[](concepts::value auto i) const&&
		{
			return move(*this)[*i];
		}

		constexpr auto data() requires non_reference_type
		{
			return std::addressof(this->buffer->obj);
		}
		constexpr auto data() const requires non_reference_type
		{
			return (const T*)std::addressof(this->buffer->obj);
		}

		constexpr auto count() const noexcept
		{
			return C;
		}

		using type = T;
		static constexpr auto value = C;
	};

	array(auto, concepts::type auto t, auto&&... args)
		-> array<PP_GET_TYPE(t), sizeof...(args)>;

	namespace detail
	{
		template <typename T>
		concept array_concept = requires(T t)
		{
			[]<typename U, size_t C>(const array<U, C>&)
			{
			}(t);
		};
	}

	template <typename ResultType>
	struct array_iterator_transform
	{
		constexpr auto&& operator()(auto&& wrap) const
		{
			return ResultType(wrap.obj);
		}
	};

	template <typename T, typename ResultType>
	struct array_iterator
		: public transform_iterator<T*, array_iterator_transform<ResultType>>
	{
		using base =
			transform_iterator<T*, array_iterator_transform<ResultType>>;

		constexpr array_iterator(T* p) noexcept
			: base(p, array_iterator_transform<ResultType>{})
		{}
		constexpr array_iterator(T* p, concepts::type auto) noexcept
			: array_iterator(p)
		{}

		constexpr operator auto()
		{
			return std::addressof(this->inner_iterator()->obj);
		}
	};
	template <typename T>
	array_iterator(T* p, concepts::type auto t)
		-> array_iterator<T, PP_GET_TYPE(t)>;

	namespace detail
	{
		struct array_helper
		{
			static constexpr auto begin(auto&& a) noexcept
			{
				constexpr auto array_type = PP_DECLTYPE(a);
				constexpr auto array_type_no_cvref = ~array_type;
				constexpr auto result_type =
					copy_cvref(array_type, get_type(array_type_no_cvref));

				if constexpr (-array_type_no_cvref != 0)
					return array_iterator(+a.buffer, result_type);
				else
					return Template<empty_iterator>(result_type)();
			}
			static constexpr auto end(auto&& a) noexcept
			{
				return begin(PP_FORWARD(a)) + a.value;
			}
		};
	}

	constexpr auto begin(detail::array_concept auto&& a) noexcept
	{
		return detail::array_helper::begin(PP_FORWARD(a));
	}
	constexpr auto end(detail::array_concept auto&& a) noexcept
	{
		return detail::array_helper::end(PP_FORWARD(a));
	}

	constexpr inline auto first_or = PP::make_overloaded_pack(
		id_forward,
		[](auto&&, auto&& head, auto&&...) -> decltype(auto)
		{
			return PP_FORWARD(head);
		});

	PP_FUNCTOR(init_array,
			   concepts::value auto do_init,
			   concepts::type auto t,
			   auto&&... args)
	{
		return array(conditional(do_init, in_place, placeholder),
					 t,
					 PP_FORWARD(args)...);
	});

	constexpr inline auto construct_array = init_array * value_false;

	PP_FUNCTOR(make_array, auto&&... args)
	{
		return construct_array(first_or(PP::type<char>, ~PP_DECLTYPE(args)...),
							   PP_FORWARD(args)...);
	});
	PP_FUNCTOR(forward_as_array, auto&&... args)
	{
		return construct_array(first_or(PP::type<char>, PP_DECLTYPE(args)...),
							   PP_FORWARD(args)...);
	});
}

template <typename T, PP::size_t C>
constexpr auto&& PP::array<T, C>::operator[](size_t i) &
{
	return begin(*this)[i];
}

template <typename T, PP::size_t C>
constexpr auto&& PP::array<T, C>::operator[](size_t i) const&
{
	return begin(*this)[i];
}

template <typename T, PP::size_t C>
constexpr auto&& PP::array<T, C>::operator[](size_t i) &&
{
	return begin(move(*this))[i];
}

template <typename T, PP::size_t C>
constexpr auto&& PP::array<T, C>::operator[](size_t i) const&&
{
	return begin(move(*this))[i];
}

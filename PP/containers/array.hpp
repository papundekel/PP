#pragma once
#include <memory>
#include <type_traits>

#include "../apply_template.hpp"
#include "../apply_transform.hpp"
#include "../concepts/reference.hpp"
#include "../conditional.hpp"
#include "../construct_pack.hpp"
#include "../copy_cvref.hpp"
#include "../decompose_template.hpp"
#include "../empty.hpp"
#include "../empty_iterator.hpp"
#include "../forward_wrap.hpp"
#include "../functor.hpp"
#include "../get_value.hpp"
#include "../id.hpp"
#include "../remove_cvref.hpp"
#include "../remove_pointer.hpp"
#include "../size_t.hpp"
#include "../transform_view.hpp"
#include "../tuple/map.hpp"
#include "../value_t.hpp"
#include "tuple.hpp"

namespace PP::containers
{
template <typename, size_t>
class array;
}

namespace PP::detail
{
template <typename T, typename Tag>
class array_wrap_wrap : public forward_wrap<T>
{
public:
	constexpr array_wrap_wrap(T&& arg, Tag)
	    : forward_wrap<T>(PP_F(arg))
	{}
};
template <typename T, typename Tag>
array_wrap_wrap(T&&, Tag) -> array_wrap_wrap<T, Tag>;

template <typename, typename>
struct array_iterator;
template <typename>
struct array_iterator_transform;

class array_helper;

template <typename T>
class array_wrap
{
	template <typename, size_t>
	friend class PP::containers::array;
	template <typename, size_t>
	friend class array_impl;
	template <typename, typename>
	friend class PP::detail::array_iterator;
	template <typename>
	friend class PP::detail::array_iterator_transform;

	T obj;

	array_wrap() = default;

	template <typename U>
	constexpr array_wrap(array_wrap_wrap<U, placeholder_t> arg)
	    : obj(arg--)
	{}
	template <typename U>
	constexpr array_wrap(array_wrap_wrap<U, in_place_t> i)
	    : obj(i())
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
	    : buffer(array_wrap_wrap{PP_F(args), tag}...)
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

namespace PP::containers
{
///
/// @brief A replacement for @ref std::array with support for references.
///
/// @tparam T The type of elements.
/// @tparam C The element count.
///
template <typename T, size_t C>
class array : private detail::array_impl<T, C>
{
	friend detail::array_helper;

	static constexpr auto non_reference_type = !concepts::reference<T>;

public:
	array() = default;

	///
	/// @brief Constructs the array depending on @p tag.
	///
	/// @param tag If @ref PP::placeholder_t, constructs using the provided
	/// values. If @ref PP::in_place_t, constructs by invoking the arguments
	/// as zero parameter functors.
	/// @param type The type of elements of the constructed array. Only used
	/// with TAD.
	/// @param args The initializers for the array elements.
	///
	constexpr array(auto tag,
	                concepts::type auto,
	                auto&&... args) requires(sizeof...(args) == C)
	    : detail::array_impl<T, C>(tag, PP_F(args)...)
	{}

	///
	/// @brief Returns the type of tuple element at certain index.
	///
	/// @param value The index. Since this is an array, this parameter is
	/// ignored.
	/// @return The type of tuple element.
	///
	constexpr auto element(concepts::value auto) const noexcept
	{
		return PP::type<T>;
	}

	///
	/// @brief Returns the tuple count.
	///
	/// @return A @ref PP::concepts::value.
	///
	constexpr auto tuple_count() const noexcept
	{
		return PP::value<C>;
	}

	///
	/// @brief Indexes the array.
	///
	/// @param i The index.
	/// @return The reference to the array element at index @p i.
	///
	constexpr auto&& operator[](size_t i) &;

	///
	/// @see operator[]()
	///
	constexpr auto&& operator[](size_t i) const&;
	///
	/// @see operator[]()
	///
	constexpr auto&& operator[](size_t i) &&;
	///
	/// @see operator[]()
	///
	constexpr auto&& operator[](size_t i) const&&;

	///
	/// @brief Indexes the array as a tuple.
	///
	/// @param i The @ref PP::concepts::value index.
	/// @return The reference to the array element at index @p i.
	///
	constexpr auto&& operator[](concepts::value auto i) &
	{
		return (*this)[*i];
	}
	///
	/// @see operator[]()
	///
	constexpr auto&& operator[](concepts::value auto i) const&
	{
		return (*this)[*i];
	}
	///
	/// @see operator[]()
	///
	constexpr auto&& operator[](concepts::value auto i) &&
	{
		return move(*this)[*i];
	}
	///
	/// @see operator[]()
	///
	constexpr auto&& operator[](concepts::value auto i) const&&
	{
		return move(*this)[*i];
	}

	///
	/// @brief Returns the address of the first element. Only available if
	/// the array element type is a non-reference type.
	///
	/// @return The addres of the first element.
	///
	constexpr auto data() requires non_reference_type
	{
		return std::addressof(this->buffer->obj);
	}
	///
	/// @see data()
	///
	constexpr auto data() const requires non_reference_type
	{
		return (const T*)std::addressof(this->buffer->obj);
	}

	///
	/// @brief Returns the number of elements.
	///
	/// @return The number of elements.
	///
	constexpr auto count() const noexcept
	{
		return C;
	}

	using type = T;

	///
	/// @brief The tuple count.
	///
	static constexpr auto value = C;
};

array(auto, concepts::type auto t, auto&&... args)
    -> array<PP_GT(t), sizeof...(args)>;

namespace detail
{
template <typename T>
concept array_concept = requires(T t)
{
	[]<typename U, size_t C>(const array<U, C>&)
	{
	}(t);
};

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
	using base = transform_iterator<T*, array_iterator_transform<ResultType>>;

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
array_iterator(T* p, concepts::type auto t) -> array_iterator<T, PP_GT(t)>;

struct array_helper
{
	static constexpr auto begin(auto&& a) noexcept
	{
		constexpr auto array_type = PP_DT(a);
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
		return begin(PP_F(a)) + a.value;
	}
};
}

constexpr auto begin(detail::array_concept auto&& a) noexcept
{
	return detail::array_helper::begin(PP_F(a));
}
constexpr auto end(detail::array_concept auto&& a) noexcept
{
	return detail::array_helper::end(PP_F(a));
}

PP_FUNCTOR(array_pick_best_type, auto&& o, concepts::tuple auto&& t)
    -> decltype(auto)
{
	if constexpr (tuple_type_count(PP_DT(t)) != 0)
		return PP_F(t)[value_0];
	else
		return PP_F(o);
});

PP_FUNCTOR(array_constructor,
           concepts::value auto do_init,
           auto&& type_functor,
           auto&&... args)
{
	return array(conditional(do_init, in_place, placeholder),
	             array_pick_best_type(PP::type<char>,
	                                  PP_FW(type_functor) +
	                                      forward_as_tuple(PP_F(args)...)),
	             PP_F(args)...);
});

PP_FUNCTOR(array_constructor_typed,
           concepts::value auto do_init,
           concepts::type auto&& type,
           auto&&... args)
{
	return array(conditional(do_init, in_place, placeholder),
	             PP_F(type),
	             PP_F(args)...);
});

constexpr inline auto init_array = array_constructor * value_true *
                                   [](auto&& arg)
{
	return PP_DT(PP_F(arg)());
};

constexpr inline auto make_array = array_constructor * value_false *
                                   [](auto&& arg)
{
	return ~PP_DT(PP_F(arg));
};
constexpr inline auto forward_as_array = array_constructor * value_false *
                                         [](auto&& arg)
{
	return PP_DT(PP_F(arg));
};
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

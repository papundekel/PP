#pragma once
#include "concepts/same_except_cvref.hpp"
#include "construct_pack.hpp"
#include "empty_tuple.hpp"
#include "empty_view.hpp"
#include "ptrdiff_t.hpp"
#include "simple_view.hpp"
#include "singular_tuple.hpp"
#include "tuple_std.hpp"
#include "tuple_find_index.hpp"
#include "tuple_get_dynamic.hpp"
#include "tuple_prepend.hpp"
#include "unique_pointer.hpp"
#include "utility/move.hpp"
#include "value_t.hpp"
#include "variant_visit.hpp"

namespace PP
{
	enum class iterator_category
	{
		forward,
		bi,
		ra
	};

	template <typename Category, typename T>
	class any_iterator_base {};

	template <typename Category, typename T>
	using any_iterator_unique_pointer = unique_pointer<pointer_stack<any_iterator_base<Category, T>, 32, alignof(std::max_align_t)>>;

	template <typename T>
	class any_iterator_base<value_t<iterator_category::forward>, T>
	{
	public:
		constexpr virtual any_iterator_unique_pointer<value_t<iterator_category::forward>, T> copy_forward() const = 0;

		constexpr virtual T dereference() const = 0;

		constexpr virtual void increment() = 0;

		constexpr virtual bool equal(const any_iterator_base& other) const = 0;

		constexpr virtual ~any_iterator_base() {}
	};

	template <typename T>
	class any_iterator_base<value_t<iterator_category::bi>, T> : public any_iterator_base<value_t<iterator_category::forward>, T>
	{
	public:
		constexpr virtual any_iterator_unique_pointer<value_t<iterator_category::bi>, T> copy_bi() const = 0;

		constexpr any_iterator_unique_pointer<value_t<iterator_category::forward>, T> copy_forward() const override final
		{
			return copy_bi();
		}

		constexpr virtual void decrement() = 0;

		constexpr virtual ~any_iterator_base() {}
	};

	template <typename T>
	class any_iterator_base<value_t<iterator_category::ra>, T> : public any_iterator_base<value_t<iterator_category::bi>, T>
	{
	public:
		constexpr virtual any_iterator_unique_pointer<value_t<iterator_category::ra>, T> copy_ra() const = 0;

		constexpr any_iterator_unique_pointer<value_t<iterator_category::bi>, T> copy_bi() const override final
		{
			return copy_ra();
		}

		constexpr virtual void advance(ptrdiff_t offset) = 0;
		constexpr virtual T index(ptrdiff_t offset) = 0;

		constexpr virtual ptrdiff_t difference(const any_iterator_base& other) const = 0;

		constexpr virtual ~any_iterator_base() {}
	};

	template <typename Iterator>
	class any_iterator_wrap
	{
	protected:
		Iterator i;

	public:
		explicit constexpr any_iterator_wrap(concepts::same_except_cvref<Iterator> auto&& i)
			: i(PP_FORWARD(i))
		{}

		constexpr decltype(auto) equal_sentinel(const auto& i_other) const
		{
			return i_other == i;
		}
		constexpr decltype(auto) difference_sentinel(const auto& i_other) const
		{
			return i_other - i;
		}
	};

	template <typename... OtherIterators>
	constexpr auto invoke_on_first_valid(auto&& f, auto def, const auto& other)
	{
		auto ptrs = make_tuple(dynamic_cast<const any_iterator_wrap<OtherIterators>*>(&other)...);
		auto i = tuple_find_index([](auto* p) { return p != nullptr; }, ptrs);

		if (i != sizeof...(OtherIterators))
			return variant_visit(PP_FORWARD(f), tuple_get_dynamic(i, ptrs));
		else
			return def;
	}

	template <typename Category, typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation {};
	template <typename Category, typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper {};

	template <typename T, typename C, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation<value_t<iterator_category::forward>, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_base<C, T>
		, public any_iterator_wrap<Iterator>
	{
	public:
		using any_iterator_wrap<Iterator>::
			any_iterator_wrap;

		constexpr T dereference() const override final
		{
			return *(this->i);
		}

		constexpr void increment() override final
		{
			++(this->i);
		}

		constexpr bool equal(const any_iterator_base<value_t<iterator_category::forward>, T>& other) const override final
		{
			return invoke_on_first_valid<Iterator, CompatibleIterators...>([this]
				(auto* ptr)
				{
					return ptr->equal_sentinel(this->i);
				}, false, other);
		}
	};

	template <typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper<value_t<iterator_category::forward>, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<value_t<iterator_category::forward>, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<value_t<iterator_category::forward>, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr any_iterator_unique_pointer<value_t<iterator_category::forward>, T> copy_forward() const override final
		{
			return make_unique_pointer(unique_tag_stack, type<any_iterator_wrapper>, this->i);
		}
	};

	template <typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation<value_t<iterator_category::bi>, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<value_t<iterator_category::forward>, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<value_t<iterator_category::forward>, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr void decrement() override final
		{
			--this->i;
		}
	};

	template <typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper<value_t<iterator_category::bi>, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<value_t<iterator_category::bi>, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<value_t<iterator_category::bi>, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr any_iterator_unique_pointer<value_t<iterator_category::bi>, T> copy_bi() const override final
		{
			return make_unique_pointer(unique_tag_stack, type<any_iterator_wrapper>, this->i);
		}
	};

	template <typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation<value_t<iterator_category::ra>, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<value_t<iterator_category::bi>, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<value_t<iterator_category::bi>, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr void advance(ptrdiff_t offset) override final
		{
			this->i += offset;
		}
		constexpr T index(ptrdiff_t offset) override final
		{
			return this->i[offset];
		}

		constexpr ptrdiff_t difference(const any_iterator_base<value_t<iterator_category::ra>, T>& other) const override final
		{
			return invoke_on_first_valid<Iterator, CompatibleIterators...>([this]
			(auto* ptr)
				{
					return ptr->difference_sentinel(this->i);
				}, (ptrdiff_t)0, other);
		}
	};

	template <typename C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper<value_t<iterator_category::ra>, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<value_t<iterator_category::ra>, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<value_t<iterator_category::ra>, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr any_iterator_unique_pointer<value_t<iterator_category::ra>, T> copy_ra() const override final
		{
			return make_unique_pointer(unique_tag_stack, type<any_iterator_wrapper>, this->i);
		}
	};

	template <typename Category, typename C, typename T>
	class any_iterator_implementation {};

	template <typename C, typename T>
	class any_iterator_implementation<value_t<iterator_category::forward>, C, T>
	{
		template <typename, typename, typename>
		friend class any_iterator_implementation;

		using pointer_type = any_iterator_unique_pointer<C, T>;

	protected:
		pointer_type p;

	public:
		constexpr any_iterator_implementation(placeholder_t, auto&& p)
			: p(move(p))
		{}

		any_iterator_implementation() = default;

		//template <template <typename> typename BaseOther>
		constexpr any_iterator_implementation(const any_iterator_implementation/*<BaseOther, T>*/& other) noexcept
			: any_iterator_implementation(placeholder, other.p->copy_forward())
		{}
		//template <template <typename> typename BaseOther>
		constexpr any_iterator_implementation(any_iterator_implementation/*<BaseOther, T>*/&& other) noexcept
			: any_iterator_implementation(placeholder, move(other.p))
		{}

		constexpr decltype(auto) operator*() const
		{
			return p->dereference();
		}
		constexpr auto operator->() const
		{
			return &**this;
		}

		constexpr auto& operator++()
		{
			p->increment();
			return *this;
		}
		constexpr auto operator++(int)
		{
			auto copy = *this;
			++copy;
			return copy;
		}

		constexpr bool operator==(const auto& other) const
		{
			return (!p && !other.p) || p->equal(*other.p);
		}
	};

	template <typename C, typename T>
	class any_iterator_implementation<value_t<iterator_category::bi>, C, T>
		: public any_iterator_implementation<value_t<iterator_category::forward>, C, T>
	{
		template <typename, typename, typename>
		friend class any_iterator_implementation;

	public:
		constexpr any_iterator_implementation(placeholder_t, auto&& p)
			: any_iterator_implementation<value_t<iterator_category::forward>, C, T>(placeholder, move(p))
		{}

		any_iterator_implementation() = default;

		//template <template <typename> typename BaseOther>
		constexpr any_iterator_implementation(const any_iterator_implementation/*<BaseOther, T>*/& other) noexcept
			: any_iterator_implementation(placeholder, other.p->copy_bi())
		{}
		//template <template <typename> typename BaseOther>
		constexpr any_iterator_implementation(any_iterator_implementation/*<BaseOther, T>*/&& other) noexcept
			: any_iterator_implementation<value_t<iterator_category::forward>, C, T>(move(other))
		{}

		constexpr auto& operator--()
		{
			this->p->decrement();
			return *this;
		}
		constexpr auto operator--(int)
		{
			auto copy = *this;
			--copy;
			return copy;
		}
	};

	template <typename C, typename T>
	class any_iterator_implementation<value_t<iterator_category::ra>, C, T>
		: public any_iterator_implementation<value_t<iterator_category::bi>, C, T>
	{
		template <typename, typename, typename>
		friend class any_iterator_implementation;

	public:
		constexpr any_iterator_implementation(placeholder_t, auto&& p)
			: any_iterator_implementation<value_t<iterator_category::bi>, C, T>(placeholder, move(p))
		{}

		any_iterator_implementation() = default;

		//template <template <typename> typename BaseOther>
		constexpr any_iterator_implementation(const any_iterator_implementation/*<BaseOther, T>*/& other) noexcept
			: any_iterator_implementation(placeholder, other.p->copy_ra())
		{}
		//template <template <typename> typename BaseOther>
		constexpr any_iterator_implementation(any_iterator_implementation/*<BaseOther, T>*/&& other) noexcept
			: any_iterator_implementation<value_t<iterator_category::bi>, C, T>(move(other))
		{}

		constexpr decltype(auto) operator-(const any_iterator_implementation<value_t<iterator_category::forward>, C, T>& other) const
		{
			return this->p->difference(*other.p);
		}

		constexpr auto& operator+=(ptrdiff_t offset)
		{
			this->p->advance(offset);
			return *this;
		}
		constexpr auto operator+(ptrdiff_t offset) const
		{
			auto copy = *this;
			copy += offset;
			return copy;
		}
		constexpr auto& operator-=(ptrdiff_t offset)
		{
			return operator+=(-offset);
		}
		constexpr auto operator-(ptrdiff_t offset) const
		{
			return *this + -offset;
		}
		constexpr decltype(auto) operator[](ptrdiff_t offset) const
		{
			return this->p->index(offset);
		}
	};

	namespace detail
	{
		constexpr auto get_iterator_category_value_t(concepts::type auto i)
		{
			constexpr auto I = PP_COPY_TYPE(i);

			if constexpr (is_iterator_ra(I))
				return value<iterator_category::ra>;
			else if constexpr (is_iterator_bi(I))
				return value<iterator_category::bi>;
			else
				return value<iterator_category::forward>;
		}

		constexpr auto make_any_iterator_implementation_type(concepts::value auto category, concepts::type auto dereference_type)
		{
			auto category_type = PP_DECLTYPE(to_value_t(category));

			return Template<any_iterator_implementation>(category_type, category_type, dereference_type);
		}
		constexpr auto make_any_iterator_wrapper_type(
			concepts::value auto category,
			concepts::type  auto dereference_type,
			concepts::type  auto iterator_type,
			concepts::tuple auto compatible_iterators)
		{
			auto category_type = PP_DECLTYPE(to_value_t(category));

			return Template<any_iterator_wrapper>[category_type += category_type += dereference_type += iterator_type += compatible_iterators];
		}

		constexpr auto make_any_iterator(concepts::iterator auto i, concepts::tuple auto compatible_iterators)
		{
			auto iterator_type = PP_DECLTYPE(i);
			auto dereference_type = PP_DECLTYPE(*i);
			auto category = get_iterator_category_value_t(iterator_type);

			return make_any_iterator_implementation_type(category, dereference_type)(
				placeholder,
				make_unique_pointer(
					unique_tag_stack,
					make_any_iterator_wrapper_type(category, dereference_type, iterator_type, compatible_iterators),
					move(i)));
		}
	}

	constexpr inline functor make_any_iterator{ overloaded {
		[](concepts::iterator auto i, concepts::tuple auto compatible_iterators) { return detail::make_any_iterator(i, compatible_iterators); },
		[](concepts::iterator auto i)											 { return detail::make_any_iterator(i, empty_tuple{}); },
	}};
	
	template <typename T>
	using any_iterator_forward = PP_GET_TYPE(detail::make_any_iterator_implementation_type(value<iterator_category::forward>, type<T>));
	template <typename T>
	using any_iterator_bi = PP_GET_TYPE(detail::make_any_iterator_implementation_type(value<iterator_category::bi>, type<T>));
	template <typename T>
	using any_iterator_ra = PP_GET_TYPE(detail::make_any_iterator_implementation_type(value<iterator_category::ra>, type<T>));
}

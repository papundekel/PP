#pragma once
#include <memory>

#include "apply_transform.hpp"
#include "arrow_operator_wrapper.hpp"
#include "concepts/atomic/returnable.hpp"
#include "concepts/convertible_to.hpp"
#include "concepts/same_except_cvref.hpp"
#include "construct_pack.hpp"
#include "empty.hpp"
#include "empty_tuple.hpp"
#include "empty_view.hpp"
#include "get_reference.hpp"
#include "ptrdiff_t.hpp"
#include "simple_view.hpp"
#include "tuple_find_dynamic.hpp"
#include "tuple_get_dynamic.hpp"
#include "tuple_prepend.hpp"
#include "tuple_std.hpp"
#include "unique_pointer.hpp"
#include "utility/move.hpp"
#include "value_t.hpp"
#include "variant_visit.hpp"

namespace PP
{
	enum class iterator_category : int
	{
		forward,
		bi,
		ra,
	};
	constexpr bool operator<=(iterator_category a, iterator_category b)
	{
		return (int)a <= (int)b;
	}
	constexpr iterator_category operator-(iterator_category a)
	{
		return iterator_category((int)a - 1);
	}

	PP_FUNCTOR(add_cv_reference, concepts::value auto cv, concepts::type auto t)
	{
		return add_reference(get_reference_value_t(t), add_cv(cv, !t));
	});

	PP_FUNCTOR(remove_cvref_or_empty, concepts::type auto t)
	{
		if constexpr (is_returnable(PP_COPY_TYPE(~t)))
			return remove_cvref(t);
		else
			return type<empty>;
	});

	namespace detail
	{
		template <typename T, typename U>
		concept at_least_type = -type<T> >= -type<U>;

		template <typename T>
		using any_iterator_const_type = apply_transform_t<add_cv_reference * value<cv_qualifier::Const>, T>;

		template <typename T>
		using any_iterator_value_type = apply_transform_t<remove_cvref_or_empty, T>;
	}

	template <iterator_category Category, typename T>
	class any_iterator_base {};

	template <iterator_category Category, typename T>
	using any_iterator_unique_pointer = unique_pointer<pointer_new<any_iterator_base<Category, T>>>;

	using any_iterator_unique_pointer_type = unique_tag_new_t;

	template <iterator_category Category, typename T>
	class any_iterator_base_base
		: public any_iterator_base<-Category, T>
	{
		using CategoryT = value_t<Category>;
		using CategoryTPrev = value_t<-Category>;

	public:
		constexpr virtual any_iterator_unique_pointer<Category, T> copy(CategoryT) const = 0;
		constexpr virtual any_iterator_unique_pointer<Category, detail::any_iterator_const_type<T>> copy_const(CategoryT) const = 0;
		constexpr virtual any_iterator_unique_pointer<Category, detail::any_iterator_value_type<T>> copy_value(CategoryT) const = 0;

		constexpr any_iterator_unique_pointer<-Category, T> copy(CategoryTPrev) const override final
		{
			return copy(CategoryT{});
		}
		constexpr any_iterator_unique_pointer<-Category, detail::any_iterator_const_type<T>> copy_const(CategoryTPrev) const override final
		{
			return copy_const(CategoryT{});
		}
		constexpr any_iterator_unique_pointer<-Category, detail::any_iterator_value_type<T>> copy_value(CategoryTPrev) const override final
		{
			return copy_value(CategoryT{});
		}
	};
	template <typename T>
	class any_iterator_base_base<iterator_category::forward, T>
	{
		using Category = value_t<iterator_category::forward>;

	public:
		constexpr auto get_type() const noexcept
		{
			return type<T>;
		}

		constexpr virtual any_iterator_unique_pointer<iterator_category::forward, T> copy(Category) const = 0;
		constexpr virtual any_iterator_unique_pointer<iterator_category::forward, detail::any_iterator_const_type<T>> copy_const(Category) const = 0;
		constexpr virtual any_iterator_unique_pointer<iterator_category::forward, detail::any_iterator_value_type<T>> copy_value(Category) const = 0;
	};

	constexpr auto any_iterator_copy_as(const auto& any_it, concepts::value auto category, concepts::type auto t)
	{
		constexpr auto from_t = PP_COPY_TYPE(any_it.get_type());

		const any_iterator_base_base<PP_GET_VALUE(category), PP_GET_TYPE(from_t)>& i = any_it;

		auto category_value_t = to_value_t(category);

		if constexpr (t == from_t)
			return i.copy(category_value_t);
		else if constexpr (t == ~from_t)
			return i.copy_value(category_value_t);
		else
			return i.copy_const(category_value_t);
	}

	template <typename T>
	class any_iterator_base<iterator_category::forward, T>
		: public any_iterator_base_base<iterator_category::forward, T>
	{
	public:
		constexpr virtual T dereference() const = 0;
		constexpr virtual void increment() = 0;
		constexpr virtual bool equal(const any_iterator_base& other) const = 0;

		constexpr virtual ~any_iterator_base() {}
	};

	template <typename T>
	class any_iterator_base<iterator_category::bi, T>
		: public any_iterator_base_base<iterator_category::bi, T>
	{
	public:
		constexpr virtual void decrement() = 0;

		constexpr virtual ~any_iterator_base() {}
	};

	template <typename T>
	class any_iterator_base<iterator_category::ra, T>
		: public any_iterator_base_base<iterator_category::ra, T>
	{
	public:
		constexpr virtual void advance(ptrdiff_t offset) = 0;
		constexpr virtual T index(ptrdiff_t offset) const = 0;
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

	//template <typename... OtherIterators>
	//constexpr auto invoke_on_first_valid(auto&& f, auto def, const auto& other)
	//{
	//	auto ptrs = make_tuple(dynamic_cast<const any_iterator_wrap<OtherIterators>*>(&other)...);
	//	auto i = tuple_find_dynamic([](auto* p) { return p != nullptr; }, ptrs);
	//
	//	if (i != sizeof...(OtherIterators))
	//		return variant_visit(PP_FORWARD(f), tuple_get_dynamic(i, ptrs));
	//	else
	//		return def;
	//}

	template <typename OtherIterator, typename... OtherIterators>
	constexpr auto invoke_on_first_valid(auto&& f, auto def, const auto& other)
	{
		auto ptr = dynamic_cast<const any_iterator_wrap<OtherIterator>*>(&other);
	
		if constexpr (sizeof...(OtherIterators) == 0)
			return def;
		else
		{
			if (ptr)
				return PP_FORWARD(f)(ptr);
			else
				return invoke_on_first_valid<OtherIterators...>(PP_FORWARD(f), def, other);
		}
	}

	template <iterator_category Category, iterator_category C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation {};

	template <typename CategoryT, typename CT, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper
		: public any_iterator_wrapper_implementation<-type<CategoryT>, -type<CT>, T, Iterator, CompatibleIterators...>
	{
		static constexpr auto Category = -type<CategoryT>;
		static constexpr auto C = -type<CT>;

		constexpr auto copy(concepts::value auto category, concepts::type auto t) const
		{
			return make_unique_pointer(
				any_iterator_unique_pointer_type{},
				type<any_iterator_wrapper<
					value_t<PP_GET_VALUE(category)>,
					CT,
					PP_GET_TYPE(t),
					Iterator,
					CompatibleIterators...>>,
				this->i);
		}

	public:
		using any_iterator_wrapper_implementation<Category, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr any_iterator_unique_pointer<Category, T> copy(CategoryT c) const override final
		{
			return copy(c, type<T>);
		}
		constexpr any_iterator_unique_pointer<Category, detail::any_iterator_const_type<T>> copy_const(CategoryT c) const override final
		{
			return copy(c, type<detail::any_iterator_const_type<T>>);
		}
		constexpr any_iterator_unique_pointer<Category, detail::any_iterator_value_type<T>> copy_value(CategoryT c) const override final
		{
			return copy(c, type<detail::any_iterator_value_type<T>>);
		}
	};

	template <iterator_category C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation<iterator_category::forward, C, T, Iterator, CompatibleIterators...>
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

		constexpr bool equal(const any_iterator_base<iterator_category::forward, T>& other) const override final
		{
			return invoke_on_first_valid<Iterator, CompatibleIterators...>([this]
				(auto* ptr)
				{
					return ptr->equal_sentinel(this->i);
				}, false, other);
		}
	};

	template <iterator_category C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation<iterator_category::bi, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<iterator_category::forward, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<iterator_category::forward, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr void decrement() override final
		{
			--this->i;
		}
	};

	template <iterator_category C, typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_wrapper_implementation<iterator_category::ra, C, T, Iterator, CompatibleIterators...>
		: public any_iterator_wrapper_implementation<iterator_category::bi, C, T, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_wrapper_implementation<iterator_category::bi, C, T, Iterator, CompatibleIterators...>::
			any_iterator_wrapper_implementation;

		constexpr void advance(ptrdiff_t offset) override final
		{
			this->i += offset;
		}
		constexpr T index(ptrdiff_t offset) const override final
		{
			return this->i[offset];
		}

		constexpr ptrdiff_t difference(const any_iterator_base<iterator_category::ra, T>& other) const override final
		{
			return invoke_on_first_valid<Iterator, CompatibleIterators...>([this]
				(auto* ptr)
				{
					return ptr->difference_sentinel(this->i);
				}, (ptrdiff_t)0, other);
		}
	};

	template <typename Category, typename C, typename T>
	class any_iterator_implementation {};

	template <typename C, typename T>
	class any_iterator_implementation<value_t<iterator_category::forward>, C, T>
	{
		template <typename, typename, typename>
		friend class any_iterator_implementation;

		using pointer_type = any_iterator_unique_pointer<-type<C>, T>;

	protected:
		pointer_type p;

	public:
		constexpr any_iterator_implementation(placeholder_t, auto&& p)
			: p(move(p))
		{}

		constexpr any_iterator_implementation(const any_iterator_implementation& other) noexcept
			: any_iterator_implementation(placeholder, any_iterator_copy_as(*other.p, value<iterator_category::forward>, type<T>))
		{}
		constexpr any_iterator_implementation(any_iterator_implementation&& other) noexcept
			: any_iterator_implementation(placeholder, move(other.p))
		{}

		template <detail::at_least_type<C> COther, concepts::convertible_to<T> U>
		constexpr any_iterator_implementation(const any_iterator_implementation<value_t<iterator_category::forward>, COther, U>& other) noexcept
			: any_iterator_implementation(placeholder, any_iterator_copy_as(*other.p, value<iterator_category::forward>, type<T>))
		{}
		template <detail::at_least_type<C> COther>
		constexpr any_iterator_implementation(any_iterator_implementation<value_t<iterator_category::forward>, COther, T>&& other) noexcept
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
			return !p && !other.p || p->equal(*other.p);
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

		constexpr any_iterator_implementation(const any_iterator_implementation& other) noexcept
			: any_iterator_implementation(placeholder, other.p->copy(value<iterator_category::bi>))
		{}
		constexpr any_iterator_implementation(any_iterator_implementation&& other) noexcept
			: any_iterator_implementation<value_t<iterator_category::forward>, C, T>(move(other))
		{}

		template <detail::at_least_type<C> COther, concepts::convertible_to<T> U>
		constexpr any_iterator_implementation(const any_iterator_implementation<value_t<iterator_category::forward>, COther, U>& other) noexcept
			: any_iterator_implementation(placeholder, any_iterator_copy_as(*other.p, value<iterator_category::bi>, type<T>))
		{}
		template <detail::at_least_type<C> COther>
		constexpr any_iterator_implementation(any_iterator_implementation<value_t<iterator_category::forward>, COther, T>&& other) noexcept
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

		constexpr any_iterator_implementation(const any_iterator_implementation& other) noexcept
			: any_iterator_implementation(placeholder, other.p->copy(value<iterator_category::ra>))
		{}
		constexpr any_iterator_implementation(any_iterator_implementation&& other) noexcept
			: any_iterator_implementation<value_t<iterator_category::bi>, C, T>(move(other))
		{}

		template <detail::at_least_type<C> COther, concepts::convertible_to<T> U>
		constexpr any_iterator_implementation(const any_iterator_implementation<value_t<iterator_category::forward>, COther, U>& other) noexcept
			: any_iterator_implementation(placeholder, any_iterator_copy_as(*other.p, value<iterator_category::ra>, type<T>))
		{}
		template <detail::at_least_type<C> COther>
		constexpr any_iterator_implementation(any_iterator_implementation<value_t<iterator_category::forward>, COther, T>&& other) noexcept
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

		constexpr auto make_any_iterator_pointer(concepts::iterator auto i, concepts::type auto dereference_type, concepts::tuple auto compatible_iterators)
		{
			auto iterator_type = PP_DECLTYPE(i);
			
			return make_unique_pointer(
				any_iterator_unique_pointer_type{},
					make_any_iterator_wrapper_type(
						get_iterator_category_value_t(iterator_type),
						dereference_type,
						iterator_type,
						compatible_iterators),
					move(i));
		}
		constexpr auto make_any_iterator(concepts::iterator auto i, concepts::tuple auto compatible_iterators)
		{
			auto iterator_type = PP_DECLTYPE(i);
			auto dereference_type = PP_DECLTYPE(*i);
			auto category = get_iterator_category_value_t(iterator_type);

			return make_any_iterator_implementation_type(category, dereference_type)(
				placeholder,
				make_any_iterator_pointer(i, dereference_type, compatible_iterators));
		}
	}

	constexpr inline auto make_any_iterator = make_overloaded_pack
	(
		[](concepts::iterator auto i, concepts::tuple auto compatible_iterators) { return detail::make_any_iterator(i, compatible_iterators); },
		[](concepts::iterator auto i)											 { return detail::make_any_iterator(i, empty_tuple{}); }
	);
	
	template <iterator_category Category, typename T>
	using any_iterator = PP_GET_TYPE(detail::make_any_iterator_implementation_type(value<Category>, type<T>));
}

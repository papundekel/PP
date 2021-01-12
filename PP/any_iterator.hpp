#pragma once
#include "unique_pointer.hpp"
#include "simple_view.hpp"

namespace PP
{
	template <template <typename> typename Base, typename T>
	using any_iterator_unique_pointer = unique_pointer<pointer_stack<Base<T>, 32, alignof(std::max_align_t)>>;
	
	template <typename T>
	class any_iterator_forward_base
	{
	public:
		constexpr virtual any_iterator_unique_pointer<any_iterator_forward_base, T> copy_forward() const = 0;

		constexpr virtual T dereference() const = 0;

		constexpr virtual void increment() = 0;

		constexpr virtual bool equal(const any_iterator_forward_base& other) const = 0;

		constexpr virtual ~any_iterator_forward_base() {}
	};

	template <typename T>
	class any_iterator_bi_base : public any_iterator_forward_base<T>
	{
	public:
		constexpr virtual any_iterator_unique_pointer<any_iterator_bi_base, T> copy_bi() const = 0;

		constexpr any_iterator_unique_pointer<any_iterator_forward_base, T> copy_forward() const override final
		{
			return copy_bi();
		}

		constexpr virtual void decrement() = 0;

		constexpr virtual ~any_iterator_bi_base() {}
	};

	template <typename T>
	class any_iterator_ra_base : public any_iterator_bi_base<T>
	{
	public:
		constexpr virtual any_iterator_unique_pointer<any_iterator_ra_base, T> copy_ra() const = 0;

		constexpr any_iterator_unique_pointer<any_iterator_bi_base, T> copy_bi() const override final
		{
			return copy_ra();
		}

		constexpr virtual void advance(std::ptrdiff_t offset) = 0;
		constexpr virtual T index(std::ptrdiff_t offset) = 0;

		constexpr virtual std::ptrdiff_t difference(const any_iterator_ra_base& other) const = 0;

		constexpr virtual ~any_iterator_ra_base() {}
	};

	template <typename Iterator>
	class any_iterator_wrap
	{
	protected:
		Iterator i;

	public:
		explicit constexpr any_iterator_wrap(auto&& i)
		requires (same_except_cvref(type_v<Iterator>, PP_DECLTYPE(i)))
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

	template <typename T>
	struct find_valid_wrap
	{
		T object;
	};

	template <typename T>
	constexpr auto operator||(find_valid_wrap<T> l, find_valid_wrap<T> r)
	{
		return l.object ? l : r;
	}

	template <typename T, typename... OtherIterators>
	constexpr auto find_valid(const any_iterator_forward_base<T>& other)
	{
		return (... || find_valid_wrap{ dynamic_cast<const any_iterator_wrap<OtherIterators>*>(&other) }).object;
	}

	template <typename T, template <typename> typename Base, typename Iterator, typename... CompatibleIterators>
	class any_iterator_forward_wrapper_implementation : public Base<T>, public any_iterator_wrap<Iterator>
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

		constexpr bool equal(const any_iterator_forward_base<T>& other) const override final
		{
			auto ptr = find_valid<Iterator, CompatibleIterators...>(other);
			return ptr && ptr->equal_sentinel(this->i);
		}
	};

	template <typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_forward_wrapper : public any_iterator_forward_wrapper_implementation<T, any_iterator_forward_base, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_forward_wrapper_implementation<T, any_iterator_forward_base, Iterator, CompatibleIterators...>::
			any_iterator_forward_wrapper_implementation;

		constexpr any_iterator_unique_pointer<any_iterator_forward_base, T> copy_forward() const override final
		{
			return make_unique(unique_tag_stack, type_v<any_iterator_forward_wrapper>, this->i);
		}
	};

	template <typename T, template <typename> typename Base, typename Iterator, typename... CompatibleIterators>
	class any_iterator_bi_wrapper_implementation : public any_iterator_forward_wrapper_implementation<T, Base, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_forward_wrapper_implementation<T, Base, Iterator, CompatibleIterators...>::
			any_iterator_forward_wrapper_implementation;

		constexpr void decrement() override final
		{
			--(this->i);
		}
	};

	template <typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_bi_wrapper : public any_iterator_bi_wrapper_implementation<T, any_iterator_bi_base, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_bi_wrapper_implementation<T, any_iterator_bi_base, Iterator, CompatibleIterators...>::
			any_iterator_bi_wrapper_implementation;

		constexpr any_iterator_unique_pointer<any_iterator_bi_base, T> copy_bi() const override final
		{
			return std::make_unique<any_iterator_bi_wrapper>(this->i);
		}
	};

	template <typename T, template <typename> typename Base, typename Iterator, typename... CompatibleIterators>
	class any_iterator_ra_wrapper_implementation : public any_iterator_bi_wrapper_implementation<T, Base, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_bi_wrapper_implementation<T, Base, Iterator, CompatibleIterators...>::
			any_iterator_bi_wrapper_implementation;

		constexpr void advance(std::ptrdiff_t offset) override final
		{
			this->i += offset;
		}
		constexpr T index(std::ptrdiff_t offset) override final
		{
			return this->i[offset];
		}

		constexpr std::ptrdiff_t difference(const any_iterator_ra_base<T>& other) const override final
		{
			auto ptr = find_valid<Iterator, CompatibleIterators...>(other);
			return ptr && ptr->difference_sentinel(this->i);
		}
	};

	template <typename T, typename Iterator, typename... CompatibleIterators>
	class any_iterator_ra_wrapper : public any_iterator_ra_wrapper_implementation<T, any_iterator_ra_base, Iterator, CompatibleIterators...>
	{
	public:
		using any_iterator_ra_wrapper_implementation<T, any_iterator_ra_base, Iterator, CompatibleIterators...>::
			any_iterator_ra_wrapper_implementation;

		constexpr any_iterator_unique_pointer<any_iterator_ra_base, T> copy_ra() const override final
		{
			return std::make_unique<any_iterator_ra_wrapper>(this->i);
		}
	};

	template <template <typename> typename Base, typename T>
	class any_iterator_forward_implementation
	{
		template <template <typename> typename P, typename U>
		friend class any_iterator_forward_implementation;

		using pointer_type = any_iterator_unique_pointer<Base, T>;

	protected:
		pointer_type p;

		explicit constexpr any_iterator_forward_implementation(pointer_type&& p)
			: p(std::move(p))
		{}

	public:
		any_iterator_forward_implementation() = default;

		constexpr any_iterator_forward_implementation(const any_iterator_forward_implementation& other) noexcept
			: p(other.p->copy_forward())
		{}

		constexpr any_iterator_forward_implementation(any_iterator_forward_implementation&& other) noexcept
			: p(std::move(other.p))
		{}

		constexpr T operator*() const
		{
			return p->dereference();
		}
		constexpr auto operator->() const
		{
			return &**this;
		}

		constexpr any_iterator_forward_implementation& operator++()
		{
			p->increment();
			return *this;
		}
		constexpr any_iterator_forward_implementation operator++(int)
		{
			auto copy = *this;
			operator++();
			return copy;
		}

		constexpr bool operator==(const auto& other) const
		{
			return (!p && !other.p) || p->equal(*other.p);
		}
	};

	template <template <typename> typename Base, typename T>
	class any_iterator_bi_implementation : public any_iterator_forward_implementation<Base, T>
	{
	public:
		using any_iterator_forward_implementation<Base, T>::
			any_iterator_forward_implementation;

		constexpr any_iterator_bi_implementation& operator--()
		{
			this->p->decrement();
			return *this;
		}
		constexpr any_iterator_bi_implementation operator--(int)
		{
			auto copy = *this;
			operator--();
			return copy;
		}
	};

	template <template <typename> typename Base, typename T>
	class any_iterator_ra_implementation : public any_iterator_bi_implementation<Base, T>
	{
	public:
		using any_iterator_bi_implementation<Base, T>::
			any_iterator_bi_implementation;

		constexpr std::ptrdiff_t operator-(const auto& other) const
		{
			return this->p->difference(*other.p);
		}

		constexpr auto& operator+=(std::ptrdiff_t offset)
		{
			this->p->advance(offset);
			return *this;
		}
		constexpr auto operator+(std::ptrdiff_t offset) const
		{
			auto copy = *this;
			operator+=(offset);
			return copy;
		}
	};

	template <typename T, template <typename> typename Base, template <typename, typename, typename...> typename Wrapper>
	class any_iterator_helper : public Base<T>
	{
	public:
		using Base<T>::Base;

		template <typename Iterator, typename... CompatibleIterators>
		constexpr any_iterator_helper(Iterator&& i, PP::type_tuple<CompatibleIterators...> = {})
			: Base<T>(std::make_unique<Wrapper<T, std::remove_cvref_t<Iterator>, CompatibleIterators...>>
				(std::forward<Iterator>(i)))
		{}
	};

	template <typename T>
	using any_iterator_forward_helper = any_iterator_forward_implementation<any_iterator_forward_base, T>;
	template <typename T>
	using any_iterator_bi_helper = any_iterator_bi_implementation<any_iterator_bi_base, T>;
	template <typename T>
	using any_iterator_ra_helper = any_iterator_ra_implementation<any_iterator_ra_base, T>;

	template <typename T>
	using any_iterator_forward = any_iterator_helper<T, any_iterator_forward_helper, any_iterator_forward_wrapper>;
	template <typename T>
	using any_iterator_bi = any_iterator_helper<T, any_iterator_bi_helper, any_iterator_bi_wrapper>;
	template <typename T>
	using any_iterator_ra = any_iterator_helper<T, any_iterator_ra_helper, any_iterator_ra_wrapper>;
	

	template <template <typename> typename Type, typename T>
	class any_view : public simple_view<Type<T>>
	{
	public:
		any_view() = default;

		constexpr any_view(const simple_view<Type<T>>& v)
			: simple_view<Type<T>>(v)
		{}
		constexpr any_view(simple_view<Type<T>>&& v)
			: simple_view<Type<T>>(std::move(v))
		{}
		constexpr any_view(concepts::view auto&& v)
		requires (!same_except_cvref(type_v<any_view>, PP_DECLTYPE(v)) && !same_except_cvref(type_v<simple_view<Type<T>>>, PP_DECLTYPE(v)))
			: simple_view<Type<T>>(
				Type<T>(begin(PP_FORWARD(v)),   view_end_iterator(PP_DECLTYPE(v))),
				Type<T>(  end(PP_FORWARD(v)), view_begin_iterator(PP_DECLTYPE(v))))
		{}
	};
}

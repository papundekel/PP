#pragma once
#include <memory>
#include "unique_pointer.hpp"
#include "type_t.h"
#include "different_cvref.hpp"
#include "simple_view.hpp"

namespace PP
{

}
template <typename T>
class any_iterator
{
	class any_iterator_base
	{
	public:
		constexpr virtual ~any_iterator_base() {}

		constexpr virtual T index(std::size_t) const = 0;

		constexpr virtual T dereference() const = 0;

		constexpr virtual void increment() = 0;

		constexpr virtual PP::unique_pointer<any_iterator_base> clone() const = 0;

		constexpr virtual bool equal(const any_iterator_base& other) const = 0;
		
		constexpr virtual std::ptrdiff_t difference(const any_iterator_base& other) const = 0;

		constexpr virtual void advance(std::size_t offset) = 0;
	};

	template <typename Iterator, typename OtherIterator>
	class any_iterator_wrapper final : public any_iterator_base
	{
		template <typename I, typename O>
		friend class any_iterator_wrapper;

		Iterator i;

	public:
		constexpr any_iterator_wrapper(const Iterator& i, type_t<OtherIterator> = {})
			: i(i)
		{}
		/*constexpr any_iterator_wrapper(Iterator&& i, type_t<OtherIterator> = {})
			: i(std::move(i))
		{}*/

		constexpr T index(std::size_t index) const override final
		{
			return i[index];
		}
		constexpr T dereference() const override final
		{
			return *i;
		}
		constexpr void increment() override final
		{
			++i;
		}

		constexpr PP::unique_pointer<any_iterator_base> clone() const override final
		{
			return new any_iterator_wrapper(i);
		}

		constexpr bool equal(const any_iterator_base& other) const override final
		{
			auto o = dynamic_cast<const any_iterator_wrapper<OtherIterator, Iterator>*>(&other);
			return o && i == o->i;
		}

		constexpr virtual std::ptrdiff_t difference(const any_iterator_base& other) const override final
		{
			auto o = dynamic_cast<const any_iterator_wrapper<OtherIterator, Iterator>*>(&other);
			return o ? i - o->i : 0;
		}

		constexpr void advance(std::size_t offset) override final
		{
			i += offset;
		}
	};
	
	PP::unique_pointer<any_iterator_base> i;

public:
	any_iterator() = default;

	constexpr any_iterator(const any_iterator& other) noexcept
		: i(other.i->clone())
	{}

	constexpr T operator*() const
	{
		return i->dereference();
	}
	constexpr auto operator->() const
	{
		return &**this;
	}

	constexpr any_iterator& operator++()
	{
		i->increment();
		return *this;
	}
	constexpr any_iterator operator++(int)
	{
		auto copy = *this;
		++*this;
		return copy;
	}

	constexpr T operator[](std::size_t index) const
	{
		return i->index(index);
	}

	constexpr bool operator==(const any_iterator& other) const
	{
		return (!i && !other.i) || i->equal(*other.i);
	}

	constexpr std::ptrdiff_t operator-(const any_iterator& other) const
	{
		return i->difference(*other.i);
	}

	constexpr auto operator+(std::size_t offset) const
	{
		auto copy = *this;
		copy.i->advance(offset);
		return copy;
	}
	template <PP::different_cvref<any_iterator> Iterator, PP::iterator OtherIterator = std::remove_cvref_t<Iterator>>
	requires PP::iterator<Iterator>
		constexpr any_iterator(Iterator&& i, type_t<OtherIterator> t = {})
		: i(new any_iterator_wrapper(std::forward<Iterator>(i), t))
	{}
};

template <typename T>
class any_view : public PP::simple_view<any_iterator<T>>
{
public:
	any_view() = default;

	constexpr any_view(const PP::simple_view<any_iterator<T>>& v)
		: PP::simple_view<any_iterator<T>>(v)
	{}
	constexpr any_view(PP::simple_view<any_iterator<T>>&& v)
		: PP::simple_view<any_iterator<T>>(std::move(v))
	{}
	template <PP::view View>
	requires PP::different_cvref<View, any_view>&& PP::different_cvref<View, PP::simple_view<any_iterator<T>>>
		constexpr any_view(View&& v)
		: PP::simple_view<any_iterator<T>>(
			any_iterator<T>(PP::begin(std::forward<View>(v)), type_t<PP::end_t<View>>{}),
			any_iterator<T>(PP::end(std::forward<View>(v)), type_t<PP::begin_t<View>>{}))
	{}
};

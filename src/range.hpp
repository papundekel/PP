#pragma once
#include <initializer_list>
#include "sentinel.hpp"
#include "container.hpp"
#include "max.hpp"
#include "min.hpp"
#include "iterator_ra.hpp"
#include "prev.hpp"
#include "value_t.hpp"
#include "is_template.hpp"
#include "conditional.hpp"

template <typename it, typename it_end = it>
requires iterator<it>::v && sentinel<it_end, it>::v
struct range
{
	using begin_t = it;
	using end_t = it_end;
	static constexpr bool random_access = iterator_ra<it>::v && iterator_ra<it_end>::v;
	static constexpr bool finite = !same<infinity, it_end>::v;

	mutable it begin;
	mutable it_end end;

	template <typename C>
	requires container<C>::v
	explicit range(C& c)
		: begin(::begin(c))
		, end(::end(c))
	{}
	template <typename T>
	range(const std::initializer_list<T>& list)
		: begin(::begin(list))
		, end(::end(list))
	{}
	range(it begin, it_end end)
		: begin(begin)
		, end(end)
	{}
	range(range other, it_end end)
		: begin(other.begin)
		, end(end)
	{}
	range(it begin, range other)
		: begin(begin)
		, end(other.end)
	{}

	auto operator+() const
	{
		return begin;
	}
	auto operator-() const
	{
		return end;
	}
	decltype(auto) operator*()
	{
		return *begin;
	}
	decltype(auto) operator&()
	requires iterator<it_end>::v
	{
		return *end;
	}
	decltype(auto) operator++()
	{
		++begin;
		return *this;
	}
	decltype(auto) operator++(int)
	requires iterator<it_end>::v
	{
		++end;
		return *this;
	}
	decltype(auto) operator--()
	requires iterator_bi<it>::v
	{
		--begin;
		return *this;
	}
	decltype(auto) operator--(int)
	requires iterator_bi<it_end>::v
	{
		--end;
		return *this;
	}
	range operator+(size_t shift) const
	{
		if constexpr (random_access)
			return range(min(begin + shift, end), end);
		else 
		{
			auto result = *this;
			for (size_t i = 0; i != shift && result; ++result, ++i);
			return result;
		}
	}

	range operator-(size_t shift) const
	{
		if constexpr (random_access)
			return range(begin, max(begin, end - shift));
		else 
		{
			auto result = *this;
			for (size_t i = 0; i != shift && result; result--, ++i);
			return result;
		}
	}

	decltype(auto) first()
	{
		return *begin;
	}
	decltype(auto) last()
	{
		return *prev(end);
	}
	bool empty() const
	{
		return begin == end;
	}
	operator bool() const
	{
		return !empty();
	}
	size_t count() const
	{
		if constexpr (random_access)
			return end - begin;
		else
		{
			size_t hops = 0;
			for (; !empty(); ++hops, ++begin);
			return hops;
		}
	}
	bool contains(it i) const
	{
		if constexpr (random_access)
			return i >= begin && i < end;
		else
		{
			auto j = begin;
			for (; j != end && j != i; ++j);
			return j != end;
		}
	}
};

template <typename C>
requires container<C>::v
range(C&) -> range<begin_t<C>, end_t<C>>;
template <typename T>
range(const std::initializer_list<T>&) -> range<const T*>;

template <typename it>
requires iterator<it>::v
struct range_n
{
	using begin_t = it;
	using end_t = it;
	static constexpr bool random_access = iterator_ra<it>::v;
	static constexpr bool finite = true;

	it begin;
	size_t cnt;

	template <typename C>
	requires container<C>::v
	explicit range_n(C& c)
		: begin(::begin(c))
		, cnt(range(c).count())
	{}
	template <typename C>
	requires container<C>::v
	range_n(C& c, size_t cnt)
		: begin(::begin(c))
		, cnt(cnt)
	{}
	range_n(it begin, size_t cnt)
		: begin(begin)
		, cnt(cnt)
	{}
	template <typename T>
	range_n(const std::initializer_list<T>& list)
		: begin(::begin(list))
		, cnt(range_n(list).count())
	{}
	/*range_n(range_n other, size_t cnt)
		: begin()
		, cnt(0)
	{}
	range_n(it begin, range_n other)
		: begin()
		, cnt(0)
	{}*/

	decltype(auto) operator*()
	{
		return *begin;
	}
	decltype(auto) operator&()
	{
		return *(begin + cnt);
	}
	range_n& operator++()
	{
		++begin;
		--cnt;
		return *this;
	}
	range_n& operator++(int)
	{
		++cnt;
		return *this;
	}
	range_n& operator--()
	requires iterator_bi<it>::v
	{
		--begin;
		++cnt;
		return *this;
	}
	range_n& operator--(int)
	{
		--cnt;
		return *this;
	}
	range_n operator+(size_t shift)
	{
		begin += shift;
		cnt -= shift;
	}

	range_n operator-(size_t shift)
	{
		cnt -= shift;
	}

	decltype(auto) first()
	{
		return *begin;
	}
	decltype(auto) last()
	{
		return *(begin + (cnt - 1));
	}
	bool empty() const
	{
		return cnt == 0;
	}
	operator bool()
	{
		return !empty();
	}
	size_t count() const
	{
		return cnt;
	}
	bool contains(it i) const
	{
		if constexpr (random_access)
			return i >= begin && i < begin + cnt;
		else
		{
			auto j = begin;
			size_t k = 0;
			for (; k != cnt && j != i; ++j, ++k);
			return k != cnt;
		}
	}
};

template <typename C>
requires container<C>::v
range_n(C&) -> range_n<begin_t<C>>;
template <typename C>
requires container<C>::v
range_n(C&, size_t) -> range_n<begin_t<C>>;
template <typename T>
range_n(const std::initializer_list<T>&) -> range_n<const T*>;

template <typename T>
using range_type = OR<is_template<range>::type<T>, is_template<range_n>::type<T>>;

template <typename R>
requires range_type<R>::v
struct finite_range : value_t<R::finite> {};

namespace drange_base
{
	template <typename T>
	constexpr base<typename T::begin_t> x();

	template <typename T>
	requires !range_type<T>::v && container<T>::v
	constexpr container_base<T> x();
}

template <typename T>
requires range_type<T>::v || container<T>::v
using range_base = decltype(drange_base::x<T>());
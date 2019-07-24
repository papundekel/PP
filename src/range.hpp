#pragma once
#include <initializer_list>
#include "sentinel.hpp"
#include "container.hpp"
#include "max.hpp"
#include "min.hpp"
#include "iterator_ra.hpp"
#include "prev.hpp"
#include "value_t.hpp"

template <iterator it, sentinel<it> it_end = it>
struct range
{
	using begin_t = it;
	using end_t = it_end;
	static constexpr bool random_access = iterator_ra<it> && iterator_ra<it_end>;
	static constexpr bool finite = !same<infinity, it_end>;

	it begin;
	it_end end;

	template <container C>
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

	auto operator+()
	{
		return begin;
	}
	auto operator-()
	{
		return end;
	}
	decltype(auto) operator*()
	{
		return *begin;
	}
	decltype(auto) operator&()
	requires iterator<it_end>
	{
		return *end;
	}
	range& operator++()
	{
		++begin;
		return *this;
	}
	range& operator++(int)
	requires iterator<it_end>
	{
		++end;
		return *this;
	}
	range& operator--()
	requires iterator_bi<it>
	{
		--begin;
		return *this;
	}
	range& operator--(int)
	requires iterator_bi<it_end>
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

	decltype(auto) first() const
	{
		return *begin;
	}
	decltype(auto) last() const
	{
		return *prev(end);
	}
	bool empty() const
	{
		return begin == end;
	}
	operator bool()
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

template <container C>
range(C&) -> range<begin_t<C>, end_t<C>>;
template <typename T>
range(const std::initializer_list<T>&) -> range<const T*>;

template <iterator it>
struct range_n
{
	using begin_t = it;
	using end_t = it;
	static constexpr bool random_access = iterator_ra<it>;
	static constexpr bool finite = true;

	it begin;
	size_t cnt;

	template <container C>
	explicit range_n(C& c)
		: begin(::begin(c))
		, cnt(range_n(c).count())
	{}
	template <typename T>
	range_n(const std::initializer_list<T>& list)
		: begin(::begin(list))
		, cnt(range_n(list).count())
	{}
	range_n(it begin, size_t cnt)
		: begin(begin)
		, cnt(cnt)
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
	requires iterator_bi<it>
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

template <container C>
range_n(C&) -> range_n<begin_t<C>>;
template <typename T>
range_n(const std::initializer_list<T>&) -> range_n<const T*>;

template <typename T>
constexpr bool is_range_v = false;
template <typename it, typename it_end>
constexpr bool is_range_v<range<it, it_end>> = true;
template <typename it>
constexpr bool is_range_v<range_n<it>> = true;
template <typename T>
struct is_range : value_t<is_range_v<T>> {};
template <typename T>
concept Range = is_range_v<T>;

template <Range R>
constexpr bool is_finite_range_v = R::finite;
template <Range R>
struct is_finite_range : value_t<is_finite_range_v<R>> {};
template <Range R>
concept FiniteRange = is_finite_range_v<R>;

template <Range R>
using range_base = base<typename R::begin_t>;
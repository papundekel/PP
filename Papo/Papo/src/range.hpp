#pragma once
#include <initializer_list>
#include "sentinel.hpp"
#include "container.hpp"
#include "max.hpp"
#include "min.hpp"
#include "iterator_ra.hpp"
#include "prev.hpp"

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

	range& operator++()
	{
		++begin;
		return *this;
	}
	range& operator++(int)
	{
		++end;
		return *this;
	}
	range& operator--()
	{
		--begin;
		return *this;
	}
	range& operator--(int)
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
			for (size_t i = 0; i != shift && result.begin != end; ++result, ++i);
			return result;
		}
	}

	range operator-(size_t shift) const
	requires iterator_bi<it_end>
	{
		if constexpr (random_access)
			return range(begin, max(begin, end - shift));
		else 
		{
			auto result = *this;
			for (size_t i = 0; i != shift && result.end != begin; result--, ++i);
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

template <container C> range(C&) -> range<begin_t<C>, end_t<C>>;
template <typename T> range(const std::initializer_list<T>) -> range<const T*>;

namespace detail
{
	template<typename T>
	constexpr bool range_t = false;
	template<typename T, typename U>
	constexpr bool range_t<range<T, U>> = true;
}

template <typename T>
concept range_t = detail::range_t<T>;

namespace detail
{
	template <range_t R>
	constexpr auto base_type() -> ::base_type<typename R::begin_t>;
}
#pragma once
#include "range.hpp"
#include "constructible_template.hpp"
#include "equatable.hpp"
#include "prev.hpp"
#include "next.hpp"

template <typename A, typename B>
requires range_type<A> && range_type<B>
bool equal(A a, B b)
{
	for ( ; (a || b) && *a == *b; ++a, ++b);
	return !(a || b);
}

template <typename A, typename B>
requires (range_type<A> || constructible_template<range, const A>) && 
		 (range_type<B> || constructible_template<range, const B>) &&
		!(range_type<A> && range_type<B>)
bool equal(const A& a, const B& b)
{
	if constexpr (range_type<A>)
		return equal(a, range(b));
	else if constexpr (range_type<B>)
		return equal(range(a), b);
	else
		return equal(range(a), range(b));
}

template <typename R>
requires range_type<R> || constructible_template<range, const R>
bool equal(const R& r)
{
	if constexpr (range_type<R>)
		return equal(range(r, prev(-r)), range(next(+r), r));
	else
		return equal(range(r));
}


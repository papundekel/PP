#pragma once
#include "range.hpp"
#include "remove_cv.hpp"
#include "constructible.hpp"
#include "constructible_template.hpp"

template <typename R, typename T = remove_cv<range_base<R>>>
requires range_type<R>::v || constructible_template<range, R>::v
auto accumulate(const R& x, T init)
{
	if constexpr (range_type<R>::v)
	{
		auto r = x;
		for (; r; ++r)
			init += *r;
		return init;
	}
	else
		return accumulate(range(x), init);
}

template <typename R, typename T = remove_cv<range_base<R>>>
requires constructible<T>::v
auto accumulate(const R& x)
{
	return accumulate(x, T());
}
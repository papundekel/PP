#pragma once
#include "range.hpp"
#include "remove_cv.hpp"
#include "constructible.hpp"
#include "constructible_template.hpp"
#include "move_.hpp"
#include "forward.hpp"

template <typename R, typename T>
requires range_type(type<R>{})
auto accumulate(R r, T&& init)
{
	for (; r; ++r)
		init += *r;
	return forward<T>(init);
}

template <typename R, typename T>
requires !range_type(type<R>{}) && constructible_template<range>(type<const R>{})
auto accumulate(const R& r, T&& init)
{
	return accumulate(range(r), forward<T>(init));
}

template <typename R, typename T = decl_type<remove_cv(range_base(type<R>{}))>>
requires constructible<T>
auto accumulate(const R& r)
{
	return accumulate(r, T());
}
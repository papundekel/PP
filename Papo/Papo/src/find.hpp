#pragma once
#include "equatable.hpp"
#include "range.hpp"

template <range_t R, equatable_with<range_base<R>> T>
auto find(R r, const T& value)
{
	for (; r && *r != value; ++r);
	return r.begin;
}
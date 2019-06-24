#pragma once
#include "equatable.hpp"
#include "range.hpp"

template <range_t R, equatable_with<base_type<R>> T>
auto find(R r, const T& value)
{
	for (; !r.empty() && *r.begin != value; ++r);
	return r.begin;
}
#pragma once
#include "equatable.hpp"
#include "range.hpp"

template <range_t R, equatable_with<base_type<R>> T>
auto find(R r, const T& value)
{
	for (; r.begin != r.end && *r.begin != value; ++r.begin);
	return r.begin;
}
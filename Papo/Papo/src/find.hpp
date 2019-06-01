#pragma once
#include "is_comparable.hpp"
#include "base_type.hpp"
#include "range.hpp"

template <typename it, typename it_end, typename T>
it find(range<it, it_end> r, const T& value)
{
	static_assert(is_comparable<base_type<it>, T>, "find: value is not comparable");
	for (; r.begin != r.end && *r.begin != value; ++r.begin);
	return r.begin;
}
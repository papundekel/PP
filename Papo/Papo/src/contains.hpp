#pragma once
#include "range.hpp"
#include "find.hpp"

template <typename it, typename it_end, typename T>
bool contains(range<it, it_end> r, const T& value)
{
	static_assert(is_comparable<base_type<it>, T>, "contains: types must be comparable");
	return find(r, value) != r.end;
}
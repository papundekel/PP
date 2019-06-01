#pragma once
#include "enable_if.hpp"
#include "range.hpp"
#include "equal.hpp"

template <typename it1, typename it2>
it1 find_sub(range<it1> r, range<it2> r_sub)
{
	for (; r.begin != r.end && !equal(r_sub.begin, r_sub.end, r.begin); ++r.begin);
	return r.begin;
}
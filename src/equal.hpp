#pragma once
#include "range.hpp"
#include "equatable.hpp"

template <range_c A, range_c B>
requires equatable_with_c<range_base<A>, range_base<B>> && (A::finite || B::finite)
bool equal(A a, B b)
{
	for (;  (a || b) && *a == *b; ++a, ++b);
	return !(a || b);
}
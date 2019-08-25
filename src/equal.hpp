#pragma once
#include "range.hpp"
#include "equatable.hpp"

template <typename A, typename B>
requires range_type<A>::v && range_type<B>::v && equatable_with<range_base<A>, range_base<B>>::v && (A::finite || B::finite)
bool equal(A a, B b)
{
	for (;  (a || b) && *a == *b; ++a, ++b);
	return !(a || b);
}
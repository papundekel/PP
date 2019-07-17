#pragma once
#include "range.hpp"
#include "equatable.hpp"

template <Range First, Range Second>
requires equatable_with<range_base<First>, range_base<Second>> && (First::finite || Second::finite)
bool equal(First first, Second second)
{
	for (;  (first || second) && *first == *second; ++first, ++second);
	return !(first || second);
}
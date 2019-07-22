#pragma once
#include "destroy_at.hpp"
#include "range.hpp"

template <range_t R>
void destroy(R r)
{
	for (; r; ++r)
		destroy_at(+r);
}
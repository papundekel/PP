#pragma once
#include "destroy_at.hpp"
#include "range.hpp"

template <Range R>
void destroy(R r)
{
	for (; r; ++r)
		destroy_at(+r);
}
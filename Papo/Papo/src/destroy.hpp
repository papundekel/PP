#pragma once
#include "destroy_at.hpp"
#include "range.hpp"

template <range_t R>
void destroy(R r)
{
	for (; r.begin != r.end; ++r.begin)
		destroy_at(r.begin);
}
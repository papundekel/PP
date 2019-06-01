#pragma once
#include "destroy_at.hpp"
#include "range.hpp"

template <typename it, typename it_end>
void destroy(range<it, it_end> r)
{
	if constexpr (!is_arithmetic<base_type<it>>)
		for (; r.begin != r.end; ++r.begin)
			destroy_at(r.begin);
}
#pragma once
#include "iterator.hpp"
#include "fundamental.hpp"

template <iterator I>
void destroy_at(I i)
{
	using base = base_type<I>;

	if constexpr (!fundamental<base>)
		i->~base();
}
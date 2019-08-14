#pragma once
#include "iterator.hpp"
#include "fundamental.hpp"

template <typename I>
requires iterator<I>::v
void destroy_at(I i)
{
	using base = base<I>;

	if constexpr (!fundamental<base>::v)
		i->~base();
}
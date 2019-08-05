#pragma once
#include "iterator.hpp"
#include "fundamental.hpp"

template <iterator_c I>
void destroy_at(I i)
{
	using base = base<I>;

	if constexpr (!fundamental_v<base>)
		i->~base();
}
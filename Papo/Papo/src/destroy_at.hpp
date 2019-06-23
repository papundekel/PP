#pragma once
#include "iterator.hpp"
#include "arithmetic.hpp"
#include "pointer.hpp"

template <iterator I>
void destroy_at(I i)
{
	using base = base_t<I>;

	if constexpr (!arithmetic<base> && !pointer<base>)
		i->~base();
}
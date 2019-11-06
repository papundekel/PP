#pragma once
#include "iterator.hpp"
#include "fundamental.hpp"

template <typename I>
requires iterator<I>
void destroy_at(I i)
{
	using B = base<I>;
	if constexpr (!fundamental<B>)
		i->~B();
}
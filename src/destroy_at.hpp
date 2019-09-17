#pragma once
#include "iterator.hpp"
#include "fundamental.hpp"

template <typename I>
requires iterator(type<I>{})
void destroy_at(I i)
{
	using B = decl_type<base(type<I>{})>;
	if constexpr (!fundamental(type<B>{}))
		i->~B();
}
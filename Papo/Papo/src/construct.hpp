#pragma once
#include "iterator.hpp"
#include "get_address.hpp"
#include "constructible.hpp"
#include "const_t.hpp"

template <iterator I, typename ...Args>
requires !const_t<base_type<I>> && constructible<base_type<I>, Args...>
void construct(I i, Args&&... args)
{
	new (get_address(i)) base_type<I>(forward<Args>(args)...);
}
#pragma once
#include "iterator.hpp"
#include "get_address.hpp"
#include "constructible.hpp"
#include "const_t.hpp"

template <iterator I, typename ...Args>
requires !const_t<base_t<I>> && constructible<base_t<I>, Args...>
void construct(I i, Args&&... args)
{
	new (get_address(i)) base_t<I>(forward<Args>(args)...);
}
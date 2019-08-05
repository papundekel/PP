#pragma once
#include "iterator.hpp"
#include "const.hpp"
#include "constructible.hpp"
#include "get_address.hpp"

template <iterator_c I, typename... Args>
requires !const_c<base<I>> && constructible_c<base<I>, Args...>
void construct(I i, Args&&... args)
{
	new (get_address(i)) base<I>(forward<Args>(args)...);
}
#pragma once
#include "iterator.hpp"
#include "forward.hpp"
#include "get_address.hpp"
#include "constructible.hpp"

template <iterator it, typename ...Args>
requires constructible<base_t<it>, Args...>
void construct(it where, Args&&... args)
{
	new (get_address(where)) base_t<it>(forward<Args>(args)...);
}
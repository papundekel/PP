#pragma once
#include "iterator.hpp"
#include "const_type.hpp"
#include "constructible.hpp"
#include "get_address.hpp"

template <typename I, typename... Args>
requires iterator<I>::v && !const_type<base<I>>::v && constructible<base<I>, Args...>::v
void construct(I i, Args&&... args)
{
	new (get_address(i)) base<I>(forward<Args>(args)...);
}
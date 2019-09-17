#pragma once
#include "iterator.hpp"
#include "const_type.hpp"
#include "constructible.hpp"
#include "get_address.hpp"

template <typename I, typename... Args>
requires iterator(type<I>{}) && !const_type(base(type<I>{})) && constructible<decl_type<base(type<I>{})>, Args...>
void construct(I i, Args&&... args)
{
	new (get_address(i)) decl_type<base(type<I>{})>(forward<Args>(args)...);
}
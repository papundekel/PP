#pragma once
#include "iterator.hpp"
#include "type/const.hpp"
#include "constructible.hpp"
#include "get_address.hpp"

template <typename I, typename... Args>
requires iterator(t<I>) && !const_type(base(t<I>)) && constructible<decl_type<base(t<I>>, Args...>
void construct(I i, Args&&... args)
{
	new (get_address(i)) decl_type<base(type<I>{})>(forward<Args>(args)...);
}
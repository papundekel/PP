#pragma once
#include "find.hpp"
#include "move_.hpp"
#include "forward.hpp"

template <range_c R>
bool all_of(R r, auto f)
{
	return false;//!find(r, [f=move(f)]<typename ...Args>(Args && ... args) { return !f(forward<Args>(args)...); }).empty();
}
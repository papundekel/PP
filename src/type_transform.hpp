#pragma once
#include "type.hpp"
#include "type_join.hpp"
template <typename P, typename F>
constexpr auto transform(P p, F f)
{
	if constexpr (!empty(p))
		return join(f(first(p)), transform(rest(p), f));
	else
		return p;
}
#pragma once
#include "type.hpp"
#include "type_first.hpp"
#include "type_empty.hpp"
template <typename P, typename F>
constexpr auto apply(P p, F f)
{
	if constexpr (!empty(p))
	{
		f(first(p));
		apply(rest(p), f);
	}
}
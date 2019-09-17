#pragma once
#include "type.hpp"
#include "type_first.hpp"
#include "type_empty.hpp"
template <size_t N = 0, typename P, typename F>
constexpr auto find(P p, F f)
{
	if constexpr (empty(p))
		return N;
	if constexpr (f(first(p)))
		return N;
	else
		return find<N + 1>(rest(p), f);
}
#pragma once
#include "type.hpp"
#include "type_empty.hpp"
#include "type_first.hpp"
template <size_t N, typename P>
constexpr auto get(P p)
{    
    if constexpr (empty(p))
		return types<>{};
	else if constexpr (N == 0)
		return first(p);
	else
		return get<N - 1>(rest(p));
}

template <typename P, typename F>
constexpr auto get(P p, F f)
{
    if constexpr (empty(p))
		return types<>{};
	else if constexpr (f(first(p)))
		return first(p);
	else
		return get(rest(p), f);
}
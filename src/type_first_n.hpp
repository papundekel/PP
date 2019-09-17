#pragma once
#include "type.hpp"
#include "type_join.hpp"
template <size_t N, typename P>
constexpr auto first_n(P p)
{
	if constexpr (!empty(p))
		return join(first(p), first_n<N - 1>(p));
	else
		return p;
}
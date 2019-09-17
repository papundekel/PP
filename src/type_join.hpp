#pragma once
#include "type.hpp"
#include "type_empty.hpp"
#include "type_count.hpp"
template <typename T, typename... U>
constexpr auto join(types<T>, types<U...>) { return types<T, U...>{}; }
template <typename T, typename... U>
constexpr auto join(types<U...>, types<T>) { return types<U..., T>{}; }
template <typename P>
constexpr auto join(P p) { return p; }
template <typename P, typename R>
constexpr auto join(P p, R r)
{
	if constexpr (empty(p))
		return r;
	else if constexpr (empty(r))
		return p;
	else
		return join(join(p, first(r)), rest(r));
}
template <typename P, typename R, typename... S>
constexpr auto join(P p, R r, S... s) { return join(join(p, r), join(s...)); }
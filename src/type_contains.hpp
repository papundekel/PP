#pragma once
#include "type.hpp"
#include "find.hpp"
#include "type_count.hpp"
template <typename P, typename F>
constexpr auto contains(P p, F f)
{
	return find(p, f) != count(p);
}
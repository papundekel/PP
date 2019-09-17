#pragma once
#include "type.hpp"

template <typename P, typename T>
constexpr auto make_type(P p, T t)
{
	get(p, [t](auto x){ return size(x) >= size(t);});
}
#pragma once
#include "type.hpp"
template <typename T>
constexpr auto size(T)
{
	return sizeof(untype<T>);
}
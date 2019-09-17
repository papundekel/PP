#pragma once
#include "val.hpp"
#include "number.hpp"

template <typename T>
constexpr auto integer(T) { return false; }
template <typename T>
requires number(T{})
constexpr auto integer(T) { return (static_cast<untype<T>>(1) / static_cast<untype<T>>(2)) == 0; }
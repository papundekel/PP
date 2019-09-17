#pragma once
#include "type.hpp"
template <typename T>
constexpr auto reference_rvalue(type<T>) { return false; }
template <typename T>
constexpr auto reference_rvalue(type<T&&>) { return true; }
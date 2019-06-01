#pragma once
#include "is_integral.hpp"
#include "is_float.hpp"

template <typename T>
constexpr bool is_arithmetic = is_integral<T> || is_float<T>;
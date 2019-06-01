#pragma once
#include "is_integral_signed.hpp"
#include "is_float.hpp"

template <typename T>
constexpr bool is_signed = is_integral_signed<T> || is_float<T>;
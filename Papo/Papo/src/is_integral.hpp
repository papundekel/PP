#pragma once
#include "is_integral_signed.hpp"
#include "is_integral_unsigned.hpp"

template <typename T>
constexpr bool is_integral = is_integral_signed<T> || is_integral_unsigned<T>;
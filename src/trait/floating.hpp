#pragma once
#include "number.hpp"
#include "integer.hpp"
template <typename T>
constexpr auto floating = number<T> && !integer<T>;
#pragma once
#include "val.hpp"
#include "number.hpp"

template <typename T>
constexpr auto integer = number<T> && static_cast<T>(1) / static_cast<T>(2) == 0;
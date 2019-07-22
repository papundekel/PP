#pragma once
#include "one_of.hpp"

template <typename T>
concept floating = one_of<T, float, double, long double>;
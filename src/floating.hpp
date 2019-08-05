#pragma once
#include "one_of.hpp"

template <typename T>
concept floating_c = one_of_c<T, float, double, long double>;
#pragma once
#include "value_t.hpp"
#include "number.hpp"
template <typename T>
struct integer : value_t<number<T>::v && static_cast<T>(1) / static_cast<T>(2) == 0> {};
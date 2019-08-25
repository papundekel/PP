#pragma once
#include "number.hpp"
#include "integer.hpp"
template <typename T>
using floating = value_t<number<T>::v && !integer<T>::v>;
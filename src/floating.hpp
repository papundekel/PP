#pragma once
#include "number.hpp"
#include "integer.hpp"
template <typename T>
using floating = val<number<T>::v && !integer<T>::v>;
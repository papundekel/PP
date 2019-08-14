#pragma once
#include "number.hpp"
#include "integer.hpp"
template <typename T>
struct floating : value_t<number<T>::v && !integer<T>::v> {};
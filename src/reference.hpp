#pragma once
#include "reference_lvalue.hpp"
#include "reference_rvalue.hpp"

template <typename T>
using reference = value_t<reference_lvalue<T>::v || reference_rvalue<T>::v>;
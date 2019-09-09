#pragma once
#include "reference_lvalue.hpp"
#include "reference_rvalue.hpp"

template <typename T>
using reference = val<reference_lvalue<T>::v || reference_rvalue<T>::v>;
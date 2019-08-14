#pragma once
#include "conditional.hpp"
#include "reference.hpp"
template <typename T>
using as_lvalue = conditional<reference<T>::v, T, T&>;
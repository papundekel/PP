#pragma once
#include "conditional.hpp"
#include "reference.hpp"
template <typename T>
using as_lvalue = conditional<reference_v<T>, T, T&>;
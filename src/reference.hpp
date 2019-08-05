#pragma once
#include "reference_lvalue.hpp"
#include "reference_rvalue.hpp"

template <typename T>
concept reference_v = reference_lvalue_v<T> || reference_rvalue_v<T>;

template <typename T>
struct reference : value_t<reference_v<T>> {};

template <typename T>
concept reference_c = reference_v<T>;
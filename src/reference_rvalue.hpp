#pragma once
#include "value_t.hpp"

template <typename T>
constexpr bool reference_rvalue_v = false;
template <typename T>
constexpr bool reference_rvalue_v<T&&> = true;

template <typename T>
struct reference_rvalue : value_t<reference_rvalue_v<T>> {};

template <typename T>
concept reference_rvalue_c = reference_rvalue_v<T>;
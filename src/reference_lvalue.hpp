#pragma once
#include "value_t.hpp"

template <typename T>
constexpr bool reference_lvalue_v = false;
template <typename T>
constexpr bool reference_lvalue_v<T&> = true;

template <typename T>
struct reference_lvalue_s : value_t<reference_lvalue_v<T>> {};

template <typename T>
concept reference_lvalue_c = reference_lvalue_v<T>;
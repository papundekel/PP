#pragma once
#include "value_t.hpp"
template <typename T>
struct reference_lvalue : value_t<false> {};
template <typename T>
struct reference_lvalue<T&> : value_t<true> {};
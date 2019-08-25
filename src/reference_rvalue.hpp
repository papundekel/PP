#pragma once
#include "value_t.hpp"
template <typename T>
struct reference_rvalue : value_t<false> {};
template <typename T>
struct reference_rvalue<T&&> : value_t<true> {};
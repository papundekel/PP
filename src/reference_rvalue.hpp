#pragma once
#include "val.hpp"
template <typename T>
struct reference_rvalue : val<false> {};
template <typename T>
struct reference_rvalue<T&&> : val<true> {};
#pragma once
#include "val.hpp"
template <typename T>
struct reference_lvalue : val<false> {};
template <typename T>
struct reference_lvalue<T&> : val<true> {};
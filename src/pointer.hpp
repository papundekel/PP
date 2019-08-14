#pragma once
#include "value_t.hpp"

template <typename T>
struct pointer : value_t<false> {};
template <typename T>
struct pointer<T*> : value_t<true> {};
#pragma once
#include "same.hpp"
#include "make_volatile.hpp"
template <typename T>
constexpr auto volatile_type(T t) { return t == make_volatile(t); }
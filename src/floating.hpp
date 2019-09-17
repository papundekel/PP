#pragma once
#include "number.hpp"
#include "integer.hpp"
template <typename T>
constexpr auto floating(T t) { return number(t) && !integer(t); }
#pragma once
#include "type.hpp"
template <typename T>
constexpr auto make_const(type<T>) { return type<const T>{}; }
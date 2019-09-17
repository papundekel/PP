#pragma once
#include "type.hpp"
template <typename T>
constexpr auto make_volatile(type<T>) { return type<volatile T>{}; }
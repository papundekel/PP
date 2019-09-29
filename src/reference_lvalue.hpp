#pragma once
#include "type.hpp"
template <typename T>
constexpr auto reference_lvalue(type<T>)  { return false; }
template <typename T>
constexpr auto reference_lvalue(type<T&>) { return true; }
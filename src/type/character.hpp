#pragma once
#include "type.hpp"
#include "fundamental/chars.hpp"

template <typename T>
constexpr auto character(T t) { return contains(fundamental_chars, [t](auto x){ return x == t; }); }
#pragma once
#include "make_type.hpp"
#include "fundamental_integers_unsigned.hpp"

template <typename T>
constexpr auto make_integer_unsigned(T t) { return make_type(fundamental_integers_unsigned, t); }
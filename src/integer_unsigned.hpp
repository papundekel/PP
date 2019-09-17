#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
constexpr auto integer_unsigned(T t) { return integer(t) && !signed_type(t); }
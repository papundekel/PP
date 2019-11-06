#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
constexpr auto integer_unsigned = integer<T> && !signed_type<T>;
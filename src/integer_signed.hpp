#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
constexpr auto integer_signed_v = integer_v<T> && signed_v<T>;
template <typename T>
concept integer_signed_c = integer_signed_v<T>;
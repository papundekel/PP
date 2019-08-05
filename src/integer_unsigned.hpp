#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename I>
concept integer_unsigned_c = integer_c<I> && !signed_c<I>;

template <typename I>
constexpr bool integer_unsigned_v = integer_unsigned_c<I>;
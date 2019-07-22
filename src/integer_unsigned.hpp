#pragma once
#include "integer.hpp"
#include "signed_t.hpp"

template <integer I>
concept integer_unsigned = !signed_t<I>;
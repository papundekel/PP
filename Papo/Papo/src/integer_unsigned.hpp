#pragma once
#include "integer.hpp"
#include "number_signed.hpp"

template <integer I>
concept integer_unsigned = !number_signed<I>;
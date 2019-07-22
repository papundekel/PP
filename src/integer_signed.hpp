#pragma once
#include "integer.hpp"
#include "number_signed.hpp"

template <integer I>
concept integer_signed = number_signed<I>;
#pragma once
#include "make_type.hpp"
#include "fundamental_integers_unsigned.hpp"

template <typename T>
using make_integer_unsigned = make_type<fundamental_integers_unsigned, T>;
#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
using integer_unsigned = AND<integer<T>, NOT<signed_type<T>>>;
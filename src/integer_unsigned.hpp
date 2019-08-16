#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
using integer_unsigned = value_t<integer<T>::v && !signed_type<T>::v>;
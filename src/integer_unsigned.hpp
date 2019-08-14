#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
struct integer_unsigned : value_t<integer<T>::v && !signed_type<T>::v>::v {};
#pragma once
#include "integer.hpp"
#include "signed.hpp"

template <typename T>
using integer_signed = AND<integer<T>, signed_type<T>>;
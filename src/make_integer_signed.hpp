#pragma once
#include "make_type.hpp"
#include "fundamental_integers_signed.hpp"

template <typename T>
using make_integer_signed = make_type<fundamental_integers_signed, T>;
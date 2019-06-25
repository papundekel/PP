#pragma once
#include "number_signed.hpp"
#include "integer_unsigned.hpp"

template <typename T>
concept number = integer_unsigned<T> || number_signed<T>;
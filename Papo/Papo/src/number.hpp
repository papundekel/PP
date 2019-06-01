#pragma once
#include "number_signed.hpp"
#include "integral_unsigned.hpp"

template <typename T>
concept number = integral_unsigned<T> || number_signed<T>;
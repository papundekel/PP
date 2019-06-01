#pragma once
#include "integral_unsigned.hpp"
#include "integral_signed.hpp"

template <typename T>
concept integral = integral_signed<T> || integral_unsigned<T>;
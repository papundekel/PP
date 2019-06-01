#pragma once 
#include "number.hpp"

template <typename T>
concept fundamental = number<T> || same<T, void> || same<T, bool> || same<T, nullptr_t>;
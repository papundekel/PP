#pragma once 
#include "number.hpp"
#include "pointer.hpp"

template <typename T>
concept fundamental = number<T> || pointer<T> || same<T, void> || same<T, bool> || same<T, nullptr_t>;
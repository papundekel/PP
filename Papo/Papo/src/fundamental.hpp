#pragma once 
#include "number.hpp"
#include "pointer.hpp"
#include "one_of.hpp"

template <typename T>
concept fundamental = pointer<T> || one_of<T,
void, nullptr_t, bool,
char, wchar_t, char8_t, char16_t, char32_t,
signed char, short, int, long long,
unsigned char, unsigned short, unsigned int, unsigned long long,
float, double, long double>;
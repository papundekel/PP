#pragma once 
#include "number.hpp"
#include "pointer.hpp"
#include "character.hpp"
#include "floating.hpp"

template <typename T>
concept fundamental = pointer<T> || character<T> || floating<T> || one_of<T,
void,
nullptr_t,
bool,
signed char, short, int, long long,
unsigned char, unsigned short, unsigned int, unsigned long long>;
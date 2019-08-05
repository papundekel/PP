#pragma once 
#include "number.hpp"
#include "pointer.hpp"
#include "character.hpp"
#include "floating.hpp"

template <typename T>
concept fundamental_c = pointer_c<T> || character_c<T> || floating_c<T> || one_of_c<T,
void,
nullptr_t,
bool,
signed char, short, int, long long,
unsigned char, unsigned short, unsigned int, unsigned long long>;

template <typename T>
constexpr auto fundamental_v = fundamental_c<T>;
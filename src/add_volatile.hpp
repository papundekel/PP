#pragma once
#include "type_t.hpp"

template <typename T>
struct add_volatile : type_t<volatile T> {};
template <typename T>
using add_volatile_t = add_volatile<T>::type;
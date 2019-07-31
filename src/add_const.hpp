#pragma once
#include "type_t.hpp"

template <typename T>
struct add_const : type_t<const T> {};
template <typename T>
using add_const_t = add_const<T>::type;
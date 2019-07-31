#pragma once
#include "type_t.hpp"
template <typename T>
struct remove_const : type_t<T> {};
template <typename T>
struct remove_const<const T> : type_t<T> {};
template <typename T>
using remove_const_t = remove_const<T>::type;
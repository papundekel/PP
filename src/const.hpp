#pragma once
#include "value_t.hpp"

template <typename T>
struct is_const : value_t<false> {};
template <typename T>
struct is_const<const T> : value_t<true> {};

template <typename T>
constexpr auto is_const_v = is_const<T>::value;

template <typename T>
concept Const = is_const_v<T>;
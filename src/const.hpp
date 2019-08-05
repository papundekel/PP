#pragma once
#include "value_t.hpp"

template <typename T>
constexpr auto const_v = false;
template <typename T>
constexpr auto const_v<const T> = true;

template <typename T>
struct const_s : value_t<const_v<T>> {};

template <typename T>
concept const_c = const_v<T>;
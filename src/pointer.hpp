#pragma once
#include "value_t.hpp"

template <typename T>
constexpr bool pointer_v = false;
template <typename T>
constexpr bool pointer_v<T*> = true;

template <typename T>
struct pointer_s : value_t<pointer_v<T>> {};

template <typename T>
concept pointer_c = pointer_v<T>;
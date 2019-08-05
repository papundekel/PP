#pragma once
#include "value_t.hpp"

template <typename T, typename U, typename ...V>
constexpr bool same_v = same_v<T, U> && same_v<U, V...>;
template <typename T, typename U>
constexpr bool same_v<T, U> = false;
template <typename T>
constexpr bool same_v<T, T> = true;

template <typename T>
struct same : value_t<same_v<T>> {};

template <typename T, typename U, typename ...V>
concept same_c = same_v<T, U, V...>;
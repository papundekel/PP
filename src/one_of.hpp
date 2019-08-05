#pragma once
#include "same.hpp"

template <typename T, typename U, typename ...V>
constexpr bool one_of_v = same_v<T, U> || one_of_v<T, V...>;

template <typename T, typename U>
constexpr bool one_of_v<T, U> = same_v<T, U>;

template <typename T, typename U, typename ...V>
concept one_of_c = one_of_v<T, U, V...>;
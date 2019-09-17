#pragma once
#include "type.hpp"
template <typename T, typename... U>
constexpr auto first(types<T, U...>) { return type<T>{}; }
template <typename T, typename... U>
constexpr auto rest(types<T, U...>) { return types<U...>{}; }
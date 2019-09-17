#pragma once
#include "type.hpp"
template <typename... T>
constexpr auto count(types<T...>) { return sizeof...(T); }
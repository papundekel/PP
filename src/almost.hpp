#pragma once
#include "same.hpp"
#include "remove_cvref.hpp"

template <typename... T>
constexpr auto almost = same<remove_cvref<T>...>;
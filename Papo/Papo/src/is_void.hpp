#pragma once
#include "is_same.hpp"
#include "remove_cv.hpp"

template <typename T>
constexpr bool is_void = is_same<remove_cv<T>, void>;
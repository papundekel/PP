#pragma once
#include "val.hpp"
#include "remove_cv.hpp"

template <typename T>
constexpr auto pointer_type(T t) { return false; }
template <typename T>
constexpr auto pointer_type(type<T*> t) { return true; }
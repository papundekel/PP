#pragma once
#include "bool_t.hpp"
#include "remove_cv.hpp"

template <typename T> constexpr bool _is_pointer	 = false;
template <typename T> constexpr bool _is_pointer<T*> =  true;
template <typename T> constexpr bool  is_pointer = _is_pointer<remove_cv<T>>;
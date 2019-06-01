#pragma once
#include "bool_t.hpp"

template <typename T> constexpr bool is_reference_lvalue	 = false;
template <typename T> constexpr bool is_reference_lvalue<T&> =  true;
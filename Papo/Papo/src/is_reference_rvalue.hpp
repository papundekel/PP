#pragma once
#include "bool_t.hpp"

template <typename T> constexpr bool is_reference_rvalue	  = false;
template <typename T> constexpr bool is_reference_rvalue<T&&> =  true;
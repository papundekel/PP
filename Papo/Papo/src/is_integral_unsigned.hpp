#pragma once
#include "bool_t.hpp"
#include "remove_cv.hpp"

template <typename T> constexpr bool _is_integral_unsigned = false;
template<> constexpr bool _is_integral_unsigned<bool>				= true;
template<> constexpr bool _is_integral_unsigned<unsigned char>		= true;
template<> constexpr bool _is_integral_unsigned<unsigned short>		= true;
template<> constexpr bool _is_integral_unsigned<unsigned int>		= true;
template<> constexpr bool _is_integral_unsigned<unsigned long long> = true;

template <typename T> constexpr bool  is_integral_unsigned = _is_integral_unsigned<remove_cv<T>>;
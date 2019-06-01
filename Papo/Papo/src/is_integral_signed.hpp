#pragma once
#include "bool_t.hpp"
#include "remove_cv.hpp"

template <typename T> constexpr bool _is_integral_signed			  = false;
template <>			  constexpr bool _is_integral_signed<char>		  =  true;
template <>			  constexpr bool _is_integral_signed<signed char> =  true;
template <>			  constexpr bool _is_integral_signed<short>		  =  true;
template <>			  constexpr bool _is_integral_signed<int>		  =  true;
template <>			  constexpr bool _is_integral_signed<long long>	  =  true;

template <typename T> constexpr bool  is_integral_signed = _is_integral_signed<remove_cv<T>>;
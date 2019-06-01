#pragma once
#include "remove_cv.hpp"

template <typename T> constexpr bool _is_float			    = false;
template <>			  constexpr bool _is_float<float>	    =  true;
template <>			  constexpr bool _is_float<double>	    =  true;
template <>			  constexpr bool _is_float<long double> =  true;
template <typename T> constexpr bool is_float = _is_float<remove_cv<T>>;
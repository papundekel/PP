#pragma once
#include "conditional.hpp"

template <typename T>
struct _make_float
{
	using type = conditional<sizeof(T) == 8, double,
											 float>;
};
template <typename T>
struct _make_float<const T>
{
	using type = conditional<sizeof(T) == 8, const double,
											 const float>;
};
template <typename T>
struct _make_float<volatile T>
{
	using type = conditional<sizeof(T) == 8, volatile double,
											 volatile float>;
};
template <typename T>
struct _make_float<const volatile T>
{
	using type = conditional<sizeof(T) == 8, const volatile double,
											 const volatile float>;
};
template <typename T>
using make_float = typename _make_float<T>::type;
#pragma once
#include "conditional.hpp"

template <typename T>
struct _make_unsigned_integer
{
	using type = conditional<sizeof(T) == 1, unsigned char,
				 conditional<sizeof(T) == 2, unsigned short,
				 conditional<sizeof(T) == 4, unsigned int,
											 unsigned long long>>>;
};
template <typename T>
struct _make_unsigned_integer<const T>
{
	using type = conditional<sizeof(T) == 1, const unsigned char,
				 conditional<sizeof(T) == 2, const unsigned short,
				 conditional<sizeof(T) == 4, const unsigned int,
											 const unsigned long long>>>;
};
template <typename T>
struct _make_unsigned_integer<volatile T>
{
	using type = conditional<sizeof(T) == 1, volatile unsigned char,
				 conditional<sizeof(T) == 2, volatile unsigned short,
				 conditional<sizeof(T) == 4, volatile unsigned int,
											 volatile unsigned long long>>>;
};
template <typename T>
struct _make_unsigned_integer<const volatile T>
{
	using type = conditional<sizeof(T) == 1, const volatile unsigned char,
				 conditional<sizeof(T) == 2, const volatile unsigned short,
				 conditional<sizeof(T) == 4, const volatile unsigned int,
											 const volatile unsigned long long>>>;
};
template <typename T>
using make_unsigned_integer = typename _make_unsigned_integer<T>::type;
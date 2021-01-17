#pragma once
#include "type_tuple.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	constexpr inline auto non_void_fundamental_types = type_tuple_v<
		  decltype(nullptr)
		, float
		, double
		, long double
		, bool
		, char
		, signed char
		, unsigned char
		, wchar_t
		, short int
		, int
		, long int
		, long long int
		, unsigned short int
		, unsigned int
		, unsigned long int
		, unsigned long long int
#ifdef __cpp_char8_t
		, char8_t
#endif
#ifdef __cpp_unicode_characters
		, char16_t
		, char32_t
#endif
	>;

	constexpr inline auto fundamental_types = tuple_prepend(type_v<void>, non_void_fundamental_types);
}

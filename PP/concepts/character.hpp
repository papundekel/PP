#pragma once
#include "fundamental_types.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept character =
			char_type<T> ||
			signed_char<T> ||
			unsigned_char<T> ||
		#ifdef __cpp_char8_t
			char8<T> ||
		#endif
		#ifdef __cpp_unicode_characters
			char16<T> ||
			char32<T> ||
		#endif
			wchar<T>;
	}
}

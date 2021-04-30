#pragma once
#include "fundamental_types.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept unsigned_integer = unsigned_short<T> || unsigned_int<T> ||
								   unsigned_long<T> || unsigned_long_long<T>;
	}
}

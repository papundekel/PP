#pragma once
#include "fundamental_types.hpp"
#include "non_void_fundamental.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept fundamental = non_void_fundamental<T> || void_type<T>;
	}
}

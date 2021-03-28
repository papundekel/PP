#pragma once
#include "non_void_fundamental.hpp"
#include "fundamental_types.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T>
		concept fundamental = non_void_fundamental<T> || void_type<T>;
	}
}

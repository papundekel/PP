#pragma once
#include "atomic/referencable.hpp"
#include "object.hpp"

namespace PP
{
	constexpr inline auto is_function_pure = is_referencable && !is_object;

	namespace concepts
	{
		template <typename T>
		concept function_pure = is_function_pure(type_v<T>);
	}
}

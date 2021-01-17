#pragma once
#include "atomic/pointable.hpp"
#include "reference.hpp"

namespace PP
{
	constexpr inline auto is_function_cvref = !is_reference && !is_pointable;

	namespace concepts
	{
		template <typename T>
		concept function_cvref = is_function_cvref(type_v<T>);
	}
}

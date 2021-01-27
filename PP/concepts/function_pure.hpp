#pragma once
#include "../functional/negate.hpp"
#include "atomic/referencable.hpp"
#include "object.hpp"

namespace PP
{
	constexpr inline auto is_function_pure = is_referencable && !is_object;

	PP_CONCEPT1(function_pure)
}

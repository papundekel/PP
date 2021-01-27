#pragma once
#include "../functional/negate.hpp"
#include "../macros/simple_concept.hpp"
#include "atomic/pointable.hpp"
#include "reference.hpp"

namespace PP
{
	constexpr inline auto is_function_cvref = !is_reference && !is_pointable;

	PP_CONCEPT1(function_cvref)
}

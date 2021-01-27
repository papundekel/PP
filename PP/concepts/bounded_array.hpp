#pragma once
#include "../functional/negate.hpp"
#include "../macros/simple_concept.hpp"
#include "atomic/complete_object.hpp"
#include "atomic/returnable.hpp"

namespace PP
{
	constexpr inline auto is_bounded_array = is_complete_object && !is_returnable;

	PP_CONCEPT1(bounded_array)
}

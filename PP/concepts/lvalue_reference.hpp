#pragma once
#include "../functional/apply_partially.hpp"
#include "../functional/compose.hpp"
#include "../functional/operators.hpp"
#include "../get_reference.hpp"
#include "../macros/simple_concept.hpp"

namespace PP
{
	constexpr inline auto is_lvalue_reference = eql * ref_qualifier::lvalue | get_value | get_reference_value_t;

	PP_CONCEPT1(lvalue_reference)
}

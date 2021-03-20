#pragma once
#include "decompose_reference.hpp"
#include "functional/apply_partially_simple.hpp"
#include "functional/compose.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto get_reference_value_t = tuple_get * value_1 | decompose_reference;
}

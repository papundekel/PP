#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_volatile.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto remove_volatile =
		tuple_get * value_0 | decompose_volatile;
}

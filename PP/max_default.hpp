#pragma once
#include "functional/apply_partially_first.hpp"
#include "functional/operators.hpp"
#include "max.hpp"

namespace PP
{
	constexpr inline auto max_default = max * lst;
}

#pragma once
#include "decompose_const.hpp"
#include "functional/apply_partially_simple.hpp"
#include "functional/compose.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto remove_const = tuple_get * value_0 | decompose_const;
}

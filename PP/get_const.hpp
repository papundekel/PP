#pragma once
#include "decompose_const.hpp"
#include "functional/apply_partially_first.hpp"
#include "functional/compose.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto get_const_value_t = tuple_get * value_1 | decompose_const;
}

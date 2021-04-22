#pragma once
#include "decompose_cv.hpp"
#include "functional/apply_partially_first.hpp"
#include "functional/compose.hpp"
#include "tuple_get.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto get_cv_value_t = tuple_get * value_1 | decompose_cv;
}

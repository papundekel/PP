#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_cv.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA get_cv_value_t = tuple_get * value_1 | decompose_cv;
}

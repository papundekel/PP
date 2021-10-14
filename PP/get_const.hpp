#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_const.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA get_const_value_t = tuple::get_ * value_1 | decompose_const;
}

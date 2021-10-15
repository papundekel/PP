#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_volatile.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA remove_volatile = compose(tuple::get_ * value_0, decompose_volatile);
}

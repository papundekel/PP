#pragma once
#include "compose.hpp"
#include "decompose_const.hpp"
#include "partial_.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA remove_const = compose(tuple::get_ * value_0, decompose_const);
}

#pragma once
#include "compose.hpp"
#include "decompose_cv.hpp"
#include "partial_.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
PP_CIA get_cv_value_t = compose(tuple::get_ * value_1, decompose_cv);
}

#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "operators.hpp"

namespace PP
{
PP_CIA negate = compose * neg;
}

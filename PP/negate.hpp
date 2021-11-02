#pragma once
#include "compose.hpp"
#include "operators.hpp"
#include "partial_.hpp"

namespace PP
{
PP_CIA negate = compose * neg;
}

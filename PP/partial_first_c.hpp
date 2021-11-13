#pragma once
#include "call_reorder.hpp"
#include "compose.hpp"
#include "partial_c.hpp"

namespace PP
{
PP_CIA partial_first_c =
    compose(call_reorder(call_reorder)(), compose(partial_c, forward));
}

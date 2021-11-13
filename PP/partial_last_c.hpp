#pragma once
#include "call_reorder.hpp"
#include "partial_c.hpp"

namespace PP
{
PP_CIA partial_last_c = call_reorder(partial_c)();
}

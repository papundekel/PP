#pragma once
#include <PP/call_reorder.hpp>
#include <PP/compose.hpp>
#include <PP/partial_c.hpp>

namespace PP
{
PP_CIA partial_first_c =
    compose(call_reorder(call_reorder)(), compose(partial_c, forward));
}

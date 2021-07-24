#pragma once
#include "../compose.hpp"
#include "../macros/CIA.hpp"
#include "../value_sequence.hpp"
#include "count.hpp"

namespace PP::tuple
{
PP_CIA value_sequence_for = make_value_sequence | count_value_t;
PP_CIA type_value_sequence_for = make_value_sequence | type_count_value_t;
}

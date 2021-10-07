#pragma once
#include "../compose.hpp"
#include "../macros/CIA.hpp"
#include "../value_sequence.hpp"
#include "count.hpp"

namespace PP::tuple
{
PP_CIA value_sequence_for = value_sequence_make | count_value_t;
PP_CIA type_value_sequence_for = value_sequence_make | type_count_value_t;
}

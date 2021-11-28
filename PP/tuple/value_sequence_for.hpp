#pragma once
#include <PP/compose.hpp>
#include <PP/macros/CIA.hpp>
#include <PP/value_sequence.hpp>
#include <PP/tuple/count.hpp>

namespace PP::tuple
{
PP_CIA value_sequence_for = compose(value_sequence_make, count_value_t);
PP_CIA type_value_sequence_for =
    compose(value_sequence_make, type_count_value_t);
}

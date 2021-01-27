#pragma once
#include "functional/compose.hpp"
#include "tuple_count.hpp"
#include "value_sequence.hpp"

namespace PP
{
	constexpr inline auto tuple_value_sequence_for		= make_value_sequence | tuple_count_value_t;
	constexpr inline auto tuple_type_value_sequence_for = make_value_sequence | tuple_type_count_value_t;
}

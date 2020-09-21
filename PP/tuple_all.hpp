#pragma once
#include <tuple>
#include "all_of.hpp"
#include "tuple_map_to_array.hpp"
#include "functional/compose.hpp"

namespace PP
{
	constexpr inline auto tuple_all = all_of | tuple_map_to_array;
}

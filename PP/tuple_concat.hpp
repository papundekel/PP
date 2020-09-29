#pragma once
#include "tuple_foldr.hpp"
#include "tuple_prepend.hpp"

namespace PP
{
	constexpr inline auto tuple_concat = apply_partially<false, false>(tuple_foldr, tuple_prepend);
}

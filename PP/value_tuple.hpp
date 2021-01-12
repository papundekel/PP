#pragma once
#include "type_tuple.hpp"
#include "value_t.hpp"

namespace PP
{
	template <auto... Values>
	constexpr inline auto value_tuple_v = type_tuple_v<value_t<Values>...>;
}

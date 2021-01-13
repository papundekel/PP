#pragma once
#include "tuple.hpp"
#include "value_t.hpp"

namespace PP
{
	template <auto... Values>
	using value_tuple = tuple<value_t<Values>...>;

	template <auto... Values>
	constexpr inline auto value_tuple_v = value_tuple<Values...>{};
}

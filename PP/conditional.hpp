#pragma once
#include "type_t.hpp"
#include "get_type.hpp"

namespace PP
{
	constexpr inline auto conditional =
		[]<auto Condition>(PP::value_t<Condition> condition, auto true_value, auto false_value)
	{
		if constexpr (Condition)
			return true_value;
		else
			return false_value;
	};
}
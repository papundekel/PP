#pragma once
#include "tuple_like.hpp"
#include "value_t.hpp"
#include "functional/functor.hpp"

namespace PP
{
	constexpr inline functor tuple_get{[]<auto I>(value_t<I>, tuple_like auto&& tuple) -> decltype(auto)
	{
		return get(value_v<I>, PP_FORWARD(tuple));
	}};
}

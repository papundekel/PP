#pragma once
#include "../get_value.hpp"
#include "../value_sequence.hpp"
#include "functor.hpp"

namespace PP
{
	constexpr inline functor apply_pack([]
		<auto... I>
		(auto&& packer, auto&& selector, value_sequence<I...>) -> decltype(auto)
		{
			return PP_FORWARD(packer)(PP_FORWARD(selector)(value<I>)...);
		});
}

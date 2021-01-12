#pragma once
#include <tuple>
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"
#include "forward.hpp"

namespace PP
{
	constexpr inline auto tuple_make = apply_partially<false>(tuple_apply,
		[](auto&&... args)
		{
			return std::make_tuple(PP_FORWARD(args)...);
		});
}

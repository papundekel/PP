#pragma once
#include "tuple.hpp"
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"
#include "forward.hpp"

namespace PP
{
	constexpr inline auto tuple_make = tuple_apply(partial_tag,
		[](auto&&... args)
		{
			return make_tuple(PP_FORWARD(args)...);
		});
}

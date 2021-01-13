#pragma once
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "functional/map_arguments.hpp"
#include "forward.hpp"

namespace PP
{
	constexpr inline auto tuple_prepend = map_arguments(tuple_apply,
		[](auto&& head)
		{
			return [&head](auto&&... elements)
			{
				return forward_as_tuple(PP_FORWARD(head), PP_FORWARD(elements)...);
			};
		});
}

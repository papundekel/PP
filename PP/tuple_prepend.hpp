#pragma once
#include <tuple>
#include "tuple_apply.hpp"
#include "functional/map_arguments.hpp"
#include "forward.hpp"

namespace PP
{
	constexpr inline auto tuple_prepend = map_arguments<false>(tuple_apply,
		[](auto&& head)
		{
			return [&head](auto&&... elements)
			{
				return std::tuple<decltype(head), decltype(elements)...>
					(PP_FORWARD(head), PP_FORWARD(elements)...);
			};
		});
}

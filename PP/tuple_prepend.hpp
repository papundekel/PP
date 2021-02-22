#pragma once
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "utility/forward.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_prepend, auto&& head, concepts::tuple auto&& t)
	{
		return functor([&head]
			(auto&&... elements)
			{
				return forward_as_tuple(PP_FORWARD(head), PP_FORWARD(elements)...);
			})[PP_FORWARD(t)];
	});

	constexpr auto operator+=(auto&& x, concepts::tuple auto&& t) noexcept
	{
		return tuple_prepend(PP_FORWARD(x), PP_FORWARD(t));
	}
}

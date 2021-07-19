#pragma once
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "utility/forward.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_prepend, auto&& head, concepts::tuple auto&& t)
	{
		return functor(
			[&head](auto&&... elements)
			{
				return forward_as_tuple(PP_F(head), PP_F(elements)...);
			})[PP_F(t)];
	});

	constexpr auto operator+=(auto&& x, concepts::tuple auto&& t) noexcept
	{
		return tuple_prepend(PP_F(x), PP_F(t));
	}
}

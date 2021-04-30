#pragma once
#include "../forward_wrap.hpp"
#include "../get_value.hpp"

namespace PP
{
	PP_FUNCTOR(apply_partially_first, auto&& f, auto&& arg)
	{
		return functor(
			[f = unwrap_functor(PP_FORWARD(f)),
			 arg = PP_FORWARD(arg)](auto&&... other_args) -> decltype(auto)
			{
				return f(arg, PP_FORWARD(other_args)...);
			});
	});

	constexpr auto operator*(concepts::functor auto&& f, auto&& arg) noexcept
	{
		return apply_partially_first(unwrap_functor(PP_FORWARD(f)),
									 PP_FORWARD(arg));
	}
}

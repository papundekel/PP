#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "functor_or_wrap.hpp"
#include "get_value.hpp"

namespace PP
{
	PP_FUNCTOR(apply_partially_first, auto&& f, auto&& arg)
	{
		return functor(
			[f = unwrap_functor(PP_FORWARD(f)),
			 a = unwrap_functor(PP_FORWARD(arg))](
				auto&&... other_args) -> decltype(auto)
			{
				return unwrap_functor_or_wrap(f)(unwrap_functor_or_wrap(a),
												 PP_FORWARD(other_args)...);
			});
	});

	constexpr auto operator*(concepts::functor_or_wrap auto&& f,
							 auto&& arg) noexcept
	{
		return apply_partially_first(unwrap_functor(PP_FORWARD(f)),
									 unwrap_functor(PP_FORWARD(arg)));
	}
}

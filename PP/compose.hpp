#pragma once
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "functor_or_wrap.hpp"

namespace PP
{
	PP_FUNCTOR(compose, auto&& f, auto&& g)
	{
		return functor(
			[
				ff = unwrap_functor(PP_FORWARD(f)),
				gg = unwrap_functor(PP_FORWARD(g))
			](auto&&... args) -> decltype(auto) requires requires
			{
				unwrap_functor_or_wrap(unwrap_functor(PP_FORWARD(f)))(
					unwrap_functor_or_wrap(PP_FORWARD(g))(PP_FORWARD(args)...));
			}
			{
				return unwrap_functor_or_wrap(ff)(
					unwrap_functor_or_wrap(gg)(PP_FORWARD(args)...));
			});
	});

	constexpr auto operator|(concepts::functor_or_wrap auto&& f,
							 concepts::functor_or_wrap auto&& g)
	{
		return compose(unwrap_functor(PP_FORWARD(f)),
					   unwrap_functor(PP_FORWARD(g)));
	}
}

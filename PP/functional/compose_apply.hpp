#pragma once
#include "applier.hpp"
#include "compose.hpp"

namespace PP
{
	PP_FUNCTOR(compose_apply, auto&& f, auto&& g)
	{
		return compose(applier(PP_FORWARD(f)), PP_FORWARD(g));
	}};

	constexpr auto operator^(concepts::functor auto&& f, concepts::functor auto&& g)
	{
		return compose_apply(unwrap_functor(PP_FORWARD(f)), unwrap_functor(PP_FORWARD(g)));
	}
}

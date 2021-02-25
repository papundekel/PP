#pragma once
#include "../tuple_apply.hpp"
#include "apply_partially.hpp"

namespace PP
{
	PP_FUNCTOR(applier, auto&& f)
	{
		return tuple_apply * unwrap_functor(PP_FORWARD(f));
	});

	constexpr auto operator*(concepts::functor auto&& f)
	{
		return applier(unwrap_functor(PP_FORWARD(f)));
	}
}

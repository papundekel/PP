#pragma once
#include "apply_partially.hpp"
#include "tuple_apply.hpp"

namespace PP
{
	PP_FUNCTOR(applier, auto&& f)
	{
		return tuple_apply * unwrap_functor(PP_F(f));
	});

	constexpr auto operator*(concepts::functor auto&& f)
	{
		return applier(unwrap_functor(PP_F(f)));
	}
}

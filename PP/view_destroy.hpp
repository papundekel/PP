#pragma once
#include "functional/apply_partially_simple.hpp"
#include "get_type.hpp"
#include "view_for_each.hpp"

namespace PP
{
	constexpr inline auto view_destroy = view_for_each * functor([]
		(auto&& x)
		{
			using T = PP_GET_TYPE(~PP_DECLTYPE(x));
			x.~T();
		});
}

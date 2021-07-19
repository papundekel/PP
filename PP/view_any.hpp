#pragma once
#include "view.hpp"
#include "view_find.hpp"

namespace PPreflection
{
	PP_FUNCTOR(view_any, auto&& predicate, concepts::view auto&& v)
	{
		return view_find(PP_F(predicate), PP_F(v)) != view_end(PP_F(v));
	});
}

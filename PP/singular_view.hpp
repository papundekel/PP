#pragma once
#include "simple_view.hpp"

namespace PP
{
	PP_FUNCTOR(make_singular_view, auto& object)
	{
		return simple_view(&object, &object + 1);
	});
}

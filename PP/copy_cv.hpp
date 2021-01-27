#pragma once
#include "get_cv.hpp"
#include "add_cv.hpp"

namespace PP
{
	PP_FUNCTOR(copy_cv, concepts::type auto from, concepts::type auto to)
	{
		return add_cv(get_cv(from), to);
	}};
}

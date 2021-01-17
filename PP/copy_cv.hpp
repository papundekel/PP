#pragma once
#include "get_cv.hpp"
#include "add_cv.hpp"

namespace PP
{
	PP_FUNCTOR(copy_cv, type_wrap auto from, type_wrap auto to)
	{
		return add_cv(get_cv(from), to);
	}};
}

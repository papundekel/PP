#pragma once
#include "add_const.hpp"
#include "add_volatile.hpp"
#include "cv_qualifier.hpp"
#include "get_value.hpp"

namespace PP
{
	PP_FUNCTOR(add_cv, value_wrap auto cv, type_wrap auto t)
	{
		constexpr auto CV = *PP_COPY_VALUE(cv);

		if constexpr (CV == cv_qualifier::none)
			return t;
		else if constexpr (CV == cv_qualifier::Const)
			return add_const(t);
		else if constexpr (CV == cv_qualifier::Volatile)
			return add_volatile(t);
		else
			return add_const(add_volatile(t));
	}};
}

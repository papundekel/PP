#pragma once
#include "../get_type_weak.hpp"
#include "../templated_dummy.hpp"

namespace PP
{
	PP_FUNCTOR(is_referencable, auto t)
	{
		return requires
		{
			typename detail::templated_dummy<PP_GET_TYPE_WEAK(t)&>;
		};
	}};
}

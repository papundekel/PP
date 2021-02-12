#pragma once
#include "size_t.hpp"
#include "tuple_view.hpp"
#include "view.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_get_dynamic, size_t i, concepts::tuple auto&& tuple)
	{
		return view_begin(make_tuple_view(PP_FORWARD(tuple)))[i];
	}};
}

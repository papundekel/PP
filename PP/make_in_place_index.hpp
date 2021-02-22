#pragma once
#include <variant>

#include "get_value.hpp"

namespace PP
{
	PP_FUNCTOR(make_in_place_index, concepts::value auto i)
	{
		return std::in_place_index<PP_GET_VALUE(i)>;
	});
}

#pragma once
#include "value_t.hpp"
#include "get_type.hpp"

namespace PP
{
	PP_FUNCTOR(type_to_value, concepts::type auto t)
	{
		return PP::value<PP_COPY_TYPE(t)>;
	}};
}

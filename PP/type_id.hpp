#pragma once
#include <typeinfo>

#include "get_type.hpp"

namespace PP
{
	PP_FUNCTOR(type_id, concepts::type auto t) -> auto&
	{
		return typeid(PP_GET_TYPE(t));
	});
}

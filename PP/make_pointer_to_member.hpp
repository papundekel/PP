#pragma once
#include "get_type.hpp"
#include "type_t.hpp"

namespace PP
{
	PP_FUNCTOR(make_pointer_to_member,
			   concepts::type auto Class,
			   concepts::type auto t)
	{
		return type<PP_GET_TYPE(t) PP_GET_TYPE(Class)::*>;
	});
}

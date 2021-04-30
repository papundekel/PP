#pragma once
#include "get_type.hpp"
#include "utility/forward.hpp"

namespace PP
{
	PP_FUNCTOR(dynamic__cast, concepts::type auto t, auto&& value)
		-> decltype(auto)
	{
		return dynamic_cast<PP_GET_TYPE(t)>(PP_FORWARD(value));
	});
}

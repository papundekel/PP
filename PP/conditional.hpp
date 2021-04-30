#pragma once
#include "functional/functor.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "type_t.hpp"

namespace PP
{
	PP_FUNCTOR(conditional,
			   concepts::value auto condition,
			   auto&&				true_value,
			   auto&&				false_value) -> decltype(auto)
	{
		if constexpr (PP_GET_VALUE(condition))
			return PP_FORWARD(true_value);
		else
			return PP_FORWARD(false_value);
	});
}

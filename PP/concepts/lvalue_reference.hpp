#pragma once
#include "../add_reference.hpp"
#include "../same.hpp"
#include "atomic/reference.hpp"

namespace PP
{
	constexpr inline auto is_lvalue_reference =
		is_reference &&
		functor{ []
		(concepts::type auto t)
		{
			return t == t + lvalue_tag;
		}};

	PP_CONCEPT1(lvalue_reference)
}

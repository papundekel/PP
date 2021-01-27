#pragma once
#include "../functional/compose.hpp"
#include "../functional/operators.hpp"
#include "../non_void_fundamental_types.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../remove_cv.hpp"
#include "../tuple_contains.hpp"
#include "../type_tuple.hpp"

namespace PP
{
	constexpr inline auto is_non_void_fundamental =
		functor{ [](concepts::type auto t)
		{
			return tuple_contains(eql * t, non_void_fundamental_types);
		}} | remove_cv;

	PP_CONCEPT1(non_void_fundamental)
}

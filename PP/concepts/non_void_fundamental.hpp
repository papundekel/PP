#pragma once
#include "../functional/compose.hpp"
#include "../fundamental_types.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../remove_cv.hpp"
#include "../tuple_contains.hpp"
#include "../type_tuple.hpp"

namespace PP
{
	constexpr inline auto is_non_void_fundamental =
		functor{ [](type_wrap auto type)
		{
			return tuple_contains(equal(partial_tag, type), non_void_fundamental_types);
		}} | remove_cv;

	namespace concepts
	{
		template <typename T>
		concept non_void_fundamental = is_non_void_fundamental(type_v<T>);
	}
}

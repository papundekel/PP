#pragma once
#include "../get_type.hpp"
#include "../macros/simple_concept.hpp"
#include "../overloaded.hpp"
#include "../size_t.hpp"

namespace PP
{
	constexpr inline auto is_bounded_array =
		make_overloaded_pack(
			[]<typename T, size_t N>(type_t<T[N]>)
			{
				return true;
			},
			[](auto)
			{
				return false;
			}) |
		to_type_t;

	PP_CONCEPT1(bounded_array)
}

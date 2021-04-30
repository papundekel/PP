#pragma once
#include "../functional/compose.hpp"
#include "../get_type.hpp"
#include "../overloaded.hpp"
#include "../remove_cv.hpp"

namespace PP
{
	constexpr inline auto is_pointer_to_member =
		make_overloaded_pack(
			[]<typename T, typename Class>(type_t<T Class::*>)
			{
				return true;
			},
			[](auto)
			{
				return false;
			}) |
		remove_cv;

	PP_CONCEPT1(pointer_to_member)
}

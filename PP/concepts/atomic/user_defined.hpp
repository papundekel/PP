#pragma once
#include "../../negate.hpp"
#include "../non_void_fundamental.hpp"
#include "../pointer.hpp"
#include "../pointer_to_member.hpp"
#include "non_array_object.hpp"

namespace PP
{
	constexpr inline auto is_user_defined =
		is_non_array_object && !is_non_void_fundamental && !is_pointer &&
		!is_pointer_to_member;
}

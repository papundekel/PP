#pragma once
#include "non_array_object.hpp"
#include "../non_void_fundamental.hpp"
#include "../pointer.hpp"
#include "../pointer_to_member.hpp"

namespace PP
{
	constexpr inline auto user_defined = is_non_array_object && !is_non_void_fundamental && !is_pointer && !is_pointer_to_member;
}

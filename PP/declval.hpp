#pragma once
#include "get_type.hpp"

namespace PP
{
	auto declval(concepts::type auto t) noexcept -> PP_GET_TYPE(t)&&;
}

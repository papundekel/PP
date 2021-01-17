#pragma once
#include "get_type.hpp"

namespace PP
{
	auto declval(type_wrap auto t) noexcept -> PP_GET_TYPE(t)&&;
}

#pragma once
#include "functional/compose.hpp"
#include "get_const.hpp"
#include "get_value.hpp"

namespace PP
{
	constexpr inline auto is_const = cv_is_const | get_value | get_const;
}

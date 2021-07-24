#pragma once
#include "compose.hpp"
#include "get_value.hpp"
#include "get_volatile.hpp"

namespace PP
{
constexpr inline auto is_volatile = cv_is_volatile | get_value | get_volatile;
}

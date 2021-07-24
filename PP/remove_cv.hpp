#pragma once
#include "compose.hpp"
#include "remove_const.hpp"
#include "remove_volatile.hpp"

namespace PP
{
constexpr inline auto remove_cv = remove_volatile | remove_const;
}

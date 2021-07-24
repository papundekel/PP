#pragma once
#include "../../conjunction.hpp"
#include "complete_object.hpp"
#include "returnable.hpp"

namespace PP
{
constexpr inline auto is_non_array_object = is_complete_object && is_returnable;
}

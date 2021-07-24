#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "decompose_const.hpp"
#include "tuple/get.hpp"
#include "value_t.hpp"

namespace PP
{
constexpr inline auto remove_const = tuple_get * value_0 | decompose_const;
}

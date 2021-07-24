#pragma once
#include "../apply_partially.hpp"
#include "../compose.hpp"
#include "../operators.hpp"
#include "../tuple.hpp"
#include "apply.hpp"
#include "fold.hpp"

namespace PP::tuple
{
constexpr inline auto disjunction = foldl * or_ * false;
}

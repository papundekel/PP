#pragma once
#include "../tuple.hpp"
#include "../tuple_fold.hpp"
#include "../tuple_apply.hpp"
#include "apply_partially.hpp"
#include "compose.hpp"
#include "constant.hpp"
#include "operators.hpp"

namespace PP
{
	constexpr inline auto disjunction = tuple_foldl * or_ * constant(false);
}

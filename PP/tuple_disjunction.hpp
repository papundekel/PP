#pragma once
#include "apply_partially.hpp"
#include "compose.hpp"
#include "constant.hpp"
#include "operators.hpp"
#include "tuple.hpp"
#include "tuple_apply.hpp"
#include "tuple_fold.hpp"

namespace PP
{
	constexpr inline auto tuple_disjunction =
		tuple_foldl * or_ * constant(false);
}

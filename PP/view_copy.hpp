#pragma once
#include "applier.hpp"
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "operators.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_copy = view_for_each * *asg | zip_view_pack;
}

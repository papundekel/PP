#pragma once
#include "functional/apply_partially_simple.hpp"
#include "functional/applier.hpp"
#include "functional/operators.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_copy = view_for_each * *asg | zip_view_pack;
}

#pragma once
#include "functional/applier.hpp"
#include "functional/apply_partially_first.hpp"
#include "functional/compose.hpp"
#include "functional/operators.hpp"
#include "move_assign.hpp"
#include "utility/move.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_move =
		view_for_each * *move_assign | zip_view_pack;
}

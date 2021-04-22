#pragma once
#include <memory>

#include "construct_at_pack.hpp"
#include "functional/apply_partially_first.hpp"
#include "functional/applier.hpp"
#include "functional/operators.hpp"
#include "utility/move.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_move_uninitialized = view_for_each * *functor([]
		(auto&& to, auto&& from)
		{
			construct_at_pack(std::addressof(to), move(from));
		}) | zip_view_pack;
}

#pragma once
#include "functional/apply_partially.hpp"
#include "utility/move.hpp"
#include "view_zip_with_pack.hpp"

namespace PP
{
	constexpr inline auto view_move = zip_with_pack * functor{ []
		(auto&& to, auto&& from)
		{
			PP_FORWARD(to) = move(from);
		}};
}

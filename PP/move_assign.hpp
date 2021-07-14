#pragma once
#include "functor.hpp"
#include "utility/move.hpp"

namespace PP
{
	PP_FUNCTOR(move_assign, auto&& x, auto&& y) -> decltype(auto)
	{
		return PP_FORWARD(x) = move(y);
	});
}

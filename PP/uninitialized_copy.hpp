#pragma once
#include "construct_at_pack.hpp"
#include "functional/apply_partially.hpp"
#include "zip_with_pack.hpp"

namespace PP
{
	constexpr inline auto uninitialized_copy = zip_with_pack * functor{ []
		(auto&& to, auto&& from)
		{
			construct_at_pack(&to, PP_FORWARD(from));
		}};
}

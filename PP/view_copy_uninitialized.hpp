#pragma once
#include "functional/apply_partially_simple.hpp"
#include "functional/applier.hpp"
#include "functional/operators.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_copy_uninitialized = view_for_each * *functor([]
		(auto&& to, auto&& from)
		{
			construct_at_pack(&to, PP_FORWARD(from));
		}) | zip_view_pack;
}

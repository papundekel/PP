#pragma once
#include <memory>

#include "applier.hpp"
#include "apply_partially_first.hpp"
#include "construct_at_pack.hpp"
#include "operators.hpp"
#include "utility/forward.hpp"
#include "view_for_each.hpp"
#include "zip_view.hpp"

namespace PP
{
	constexpr inline auto view_copy_uninitialized =
		view_for_each *
			*functor(
				[](auto&& to, auto&& from)
				{
					construct_at_pack(std::addressof(to), PP_F(from));
				}) |
		zip_view_pack;
}

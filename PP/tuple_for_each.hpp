#pragma once
#include "tuple_apply.hpp"
#include "functional/apply_partially.hpp"
#include "functional/map_arguments.hpp"
#include "functional/id.hpp"

namespace PP
{
	constexpr inline auto tuple_for_each = map_arguments<false>(tuple_apply,
		[](auto&& f)
		{
			return
				[&f](auto&&... t)
				{
					(PP_FORWARD(t)), ...);
				};
		}, id_weak);
}

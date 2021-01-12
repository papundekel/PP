#pragma once
#include <type_traits>
#include "zip_with.hpp"

namespace PP
{
	constexpr void move(view auto&& from, view auto&& to)
	{
		zip_with(
			[](auto&& from, auto&& to)
			{
				PP_FORWARD(to) = std::move(from);
			},
			PP_FORWARD(from), PP_FORWARD(to));
	}
}

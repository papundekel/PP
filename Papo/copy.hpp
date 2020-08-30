#pragma once
#include "zip_with.hpp"

namespace Papo
{
	constexpr void copy(view auto&& from, view auto&& to)
	{
		zip_with(
			[](const auto& from, auto& to)
			{
				to = from;
			},
			from, to);
	}
}

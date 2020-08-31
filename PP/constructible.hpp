#pragma once
#include "declval.hpp"

namespace PP
{
	template <typename T, typename... Args>
	concept constructible = requires
	{
		T(declval<Args>()...);
	};
}

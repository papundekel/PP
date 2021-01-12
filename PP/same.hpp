#pragma once
#include "get_type.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr auto operator==(auto t, auto u) noexcept
	{
		return to_type_t(t) == to_type_t(u);
	}
}

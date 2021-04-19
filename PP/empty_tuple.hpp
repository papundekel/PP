#pragma once
#include "size_t.hpp"

namespace PP
{
	struct zero_value
	{
		static constexpr auto value_f() noexcept
		{
			return 0_z;
		}
	};

	struct empty_tuple
	{
		constexpr auto tuple_count() const
		{
			return zero_value{};
		}
	};
}

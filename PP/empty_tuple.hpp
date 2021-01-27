#pragma once

namespace PP
{
	struct zero_value
	{
		static constexpr auto value_f() noexcept
		{
			return 0;
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

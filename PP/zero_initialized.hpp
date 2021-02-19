#pragma once

namespace PP
{
	template <typename T>
	struct zero_initialized
	{
		T value;

		constexpr zero_initialized() noexcept(noexcept(T()))
			: value()
		{}
	};
}

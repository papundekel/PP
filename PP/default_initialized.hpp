#pragma once

namespace PP
{
	template <typename T>
	struct default_initialized
	{
		T value;

		constexpr default_initialized() noexcept(noexcept(T()))
			: value()
		{}
	};
}

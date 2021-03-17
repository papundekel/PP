#pragma once

namespace PP
{
	template <typename T>
	struct ref_wrap
	{
		T& ref;

		constexpr operator T&() const noexcept
		{
			return ref;
		}
		constexpr T& get() const noexcept
		{
			return ref;
		}
	};
}

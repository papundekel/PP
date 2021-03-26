#pragma once

namespace PP
{
	template <typename T>
	class ref_wrap
	{
		T& ref;

	public:
		constexpr ref_wrap(T& ref) noexcept
			: ref(ref)
		{}

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

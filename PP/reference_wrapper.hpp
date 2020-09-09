#pragma once

namespace PP
{
	template <typename T>
	struct reference_wrapper
	{
		T* ptr;

		constexpr cref_t(T& ref) noexcept
			: ptr(&ref)
		{}
		
		constexpr T& get() const noexcept
		{
			return *ptr;
		}
		constexpr operator T&() const noexcept
		{
			return get();
		}
	};

	template <typename T>
	using cref_t = reference_wrapper<const T>;
}

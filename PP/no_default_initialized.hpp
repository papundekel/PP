#pragma once

namespace PP
{
	template <typename T>
	class no_default_initialized
	{
		T value;

	public:
		no_default_initialized() = delete;

		explicit constexpr no_default_initialized(T value) noexcept
			: value(value)
		{}

		constexpr auto get() const noexcept
		{
			return value;
		}
		constexpr operator T() const noexcept
		{
			return get();
		}

		constexpr auto& operator=(T new_value) noexcept
		{
			value = new_value;
			return *this;
		}
		
		constexpr auto& operator++() noexcept
		{
			++value;
			return *this;
		}
		constexpr auto& operator--() noexcept
		{
			--value;
			return *this;
		}

		//constexpr bool operator==(T other_value) const noexcept
		//{
		//	return value == other_value;
		//}
	};
}

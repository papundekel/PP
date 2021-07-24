#pragma once

namespace PP
{
template <typename T>
class no_default_initialized
{
	T val;

public:
	no_default_initialized() = delete;

	explicit constexpr no_default_initialized(T value) noexcept
		: val(value)
	{}

	constexpr auto get() const noexcept
	{
		return val;
	}
	constexpr operator T() const noexcept
	{
		return get();
	}

	constexpr auto& operator=(T new_value) noexcept
	{
		val = new_value;
		return *this;
	}

	constexpr auto& operator++() noexcept
	{
		++val;
		return *this;
	}
	constexpr auto& operator--() noexcept
	{
		--val;
		return *this;
	}
};
}

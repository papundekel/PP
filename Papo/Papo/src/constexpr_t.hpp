#pragma once

template <typename T, T _value>
struct constexpr_t
{
	static constexpr T value = _value;
	using value_t = T;
	constexpr operator T() const { return _value; }
};
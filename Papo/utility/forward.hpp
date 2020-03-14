#pragma once

template <typename T>
constexpr decltype(auto) forward(T& arg) noexcept
{
	return static_cast<T&&>(arg);
}
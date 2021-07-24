#pragma once

namespace PP
{
template <typename T>
constexpr T&& move(T& x) noexcept
{
	return static_cast<T&&>(x);
}
template <typename T>
constexpr T&& move(T&& x) noexcept
{
	return static_cast<T&&>(x);
}
}

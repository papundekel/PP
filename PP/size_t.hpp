#pragma once

namespace PP
{
using size_t = decltype(sizeof(0));

inline namespace literals
{
constexpr auto operator""_z(unsigned long long value) noexcept
{
	return size_t(value);
}
}
}

#pragma once

namespace PP
{
using ptrdiff_t = decltype((int*)nullptr - (int*)nullptr);

inline namespace literals
{
constexpr auto operator""_d(unsigned long long value) noexcept
{
    return ptrdiff_t(value);
}
}
}

#pragma once

namespace PP::view
{
constexpr inline struct unbounded_t
{
    friend constexpr bool operator==(auto&&, PP::view::unbounded_t) noexcept
    {
        return false;
    }
} unbounded{};
}

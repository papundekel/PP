#pragma once

namespace PP
{
struct empty {
    constexpr empty(auto&&...) noexcept
    {}
};
}

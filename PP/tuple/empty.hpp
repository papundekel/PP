#pragma once
#include "../size_t.hpp"

namespace PP
{
struct value_zero {
    static constexpr auto value_f() noexcept
    {
        return 0_z;
    }
};

struct tuple_empty {
    constexpr auto tuple_count() const
    {
        return value_zero{};
    }
};
}

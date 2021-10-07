#pragma once
#include "get_type.hpp"
#include "type_t.hpp"

constexpr auto operator==(PP::concepts::type auto t, PP::concepts::type auto u) noexcept
{
    return PP::to_type_t(t) == PP::to_type_t(u);
}

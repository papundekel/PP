#pragma once
#include "get_type.hpp"
#include "to_type_t.hpp"

constexpr auto operator==(PP::concepts::type auto&& t,
                          PP::concepts::type auto&& u) noexcept
{
    return PP::to_type_t(PP_F(t)) == PP::to_type_t(PP_F(u));
}

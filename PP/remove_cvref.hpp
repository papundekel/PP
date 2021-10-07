#pragma once
#include "compose.hpp"
#include "remove_cv.hpp"
#include "remove_reference.hpp"

namespace PP
{
PP_CIA remove_cvref = remove_cv | remove_reference;
}

constexpr auto operator~(PP::concepts::type auto t) noexcept
{
    return PP::remove_cvref(t);
}

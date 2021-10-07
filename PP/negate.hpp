#pragma once
#include "apply_partially_first.hpp"
#include "compose.hpp"
#include "functor.hpp"
#include "operators.hpp"

namespace PP
{
PP_CIA negate = compose * neg;
}

constexpr auto operator!(PP::concepts::functor auto&& f) noexcept
{
    return PP::negate(PP_F(f));
}

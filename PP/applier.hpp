#pragma once
#include "apply_partially_first.hpp"
#include "tuple/apply.hpp"

namespace PP
{
PP_CIA applier = apply_partially_first * tuple::apply;
}

constexpr auto operator++(auto&& f, int)
{
    return PP::applier(PP_F(f));
}

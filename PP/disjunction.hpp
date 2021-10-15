#pragma once
#include "apply_partially_first.hpp"
#include "combine.hpp"
#include "operators.hpp"

namespace PP
{
PP_CIA disjunction = combine * or_;
}

constexpr auto operator||(auto&& f, auto&& g)
{
    return PP::disjunction(PP_F(f), PP_F(g));
}

#pragma once
#include "apply_partially_first.hpp"
#include "combine.hpp"
#include "operators.hpp"

namespace PP
{
PP_CIA conjunction = combine * an_;
}

constexpr auto operator&&(auto&& f, auto&& g)
{
    return PP::conjunction(PP_F(f), PP_F(g));
}

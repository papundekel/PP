#pragma once
#include "apply_partially_first.hpp"
#include "combine.hpp"
#include "functor_or_wrap.hpp"
#include "operators.hpp"

namespace PP
{
PP_CIA disjunction = combine * or_;
}

constexpr auto operator||(PP::concepts::functor_or_wrap auto&& f,
                          PP::concepts::functor_or_wrap auto&& g)
{
    return PP::disjunction(PP_F(f), PP_F(g));
}

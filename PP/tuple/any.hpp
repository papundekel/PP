#pragma once
#include "../apply_partially_first.hpp"
#include "../combine.hpp"
#include "../compose.hpp"
#include "../pack/any.hpp"
#include "apply.hpp"
#include "get.hpp"

namespace PP::tuple
{
PP_CIA any =
    combine(apply, compose(apply_partially_first* pack::any, get_0), get_1);
}

constexpr decltype(auto) operator||(auto&& f, PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::any(PP_F(f), PP_F(tuple));
}

#pragma once
#include "../apply_partially_first.hpp"
#include "../pack/fold.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_CIA fold_init = combine(
    apply,
    [](auto&& left, auto&& ff, auto&& ii, auto&&)
    {
        return apply_partially_first(pack::fold_init,
                                     PP_FW(left),
                                     PP_FW(ff),
                                     PP_FW(ii));
    },
    get_3);
}

#pragma once
#include "../pack/fold.hpp"
#include "../partial_.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_CIA fold_init = combine(
    apply,
    [](auto&& left, auto&& ff, auto&& ii, auto&&)
    {
        return partial_first(pack::fold_init,
                             PP_FW(left),
                             PP_FW(ff),
                             PP_FW(ii));
    },
    pack::get_3);
}

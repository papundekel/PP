#pragma once
#include "../apply_partially_first.hpp"
#include "../constant.hpp"
#include "fold_init.hpp"

namespace PP::pack
{
PP_CIA fold = [](concepts::value auto&& left, auto&& f, auto&& i, auto&&... e)
    -> decltype(auto)
{
    return fold_init(PP_F(left), PP_F(f), constant(PP_FW(i)), PP_F(e)...);
};

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;

// PP_CIA fold1 = fold;
}

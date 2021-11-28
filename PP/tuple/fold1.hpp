#pragma once
#include <PP/combine.hpp>
#include <PP/pack/fold.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/count.hpp>

namespace PP::tuple
{
PP_CIA fold1 = combine(
    apply,
    [](auto&& left, auto&& f, auto&& t)
    {
        static_assert(type_count(PP_DT(t)) == 0, "tuple::fold1: empty tuple");

        return partial_first(pack::fold, PP_F(left), PP_F(f));
    },
    get_2);

PP_CIA foldl1 = fold1 * value_true;
PP_CIA foldr1 = fold1 * value_false;
}

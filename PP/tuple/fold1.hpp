#pragma once
#include "fold.hpp"
#include "split.hpp"

namespace PP::tuple
{
PP_CIA fold1 = [](concepts::value auto left, auto&& f, concepts::tuple auto&& t)
{
    static_assert(type_count(PP_DT(t)), "tuple::fold1: empty tuple");

    auto [head, tail] = split(PP_F(t));

    return fold(left, PP_F(f), PP_F(head), move(tail));
};

PP_CIA foldl1 = fold1 * value_true;

PP_CIA foldr1 = fold1 * value_false;
}

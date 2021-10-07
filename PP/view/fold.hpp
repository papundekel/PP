#pragma once
#include "../apply_partially_first.hpp"
#include "../functor.hpp"
#include "../get_value.hpp"
#include "../utility/move.hpp"
#include "concept.hpp"

namespace PP::view
{
PP_FUNCTOR(fold,
           concepts::value auto left,
           auto&& f,
           auto init,
           concepts::view auto&& v)
{
    if constexpr (PP_GV(left))
    {
        auto i = begin(PP_F(v));

        for (; i != end(PP_F(v)); ++i)
            init = PP_F(f)(move(init), *i);

        return tuple::make(move(i), move(init));
    }
    else
    {
        auto [begin, i] = begin_end(PP_F(v));

        if (begin != i)
        {
            do
            {
                --i;
                init = PP_F(f)(*i, move(init));
            } while (i != begin);
        }

        return tuple::make(move(i), move(init));
    }
});

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;
}

#pragma once
#include "../containers/tuple.hpp"
#include "../operators.hpp"
#include "../tuple/for_each.hpp"
#include "../tuple/make.hpp"
#include "../tuple/map.hpp"
#include "../tuple/zip_with.hpp"
#include "../utility/move.hpp"
#include "concept.hpp"

namespace PP::view
{
PP_FUNCTOR(zip_if, auto&& predicate, auto&& f, concepts::tuple auto&& views)
{
    auto begin_ends = view::begin_end + PP_F(views);
    auto is = tuple_get * value_0 + begin_ends;

    while (*neq && begin_ends)
    {
        auto dereferenced = der + is;

        auto [cond, do_step] = tuple_apply(PP_F(predicate), move(dereferenced));

        if (cond)
            tuple_apply(PP_F(f), move(dereferenced));

        tuple_for_each(value_true,
                       applier(
                           [](bool step, auto& i)
                           {
                               if (step)
                                   ++i;
                           }),
                       do_step ^ is);
    }

    return !is;
});

PP_FUNCTOR(zip_if_pack,
           auto&& predicate,
           auto&& f,
           concepts::view auto&&... views)
{
    return zip_if(PP_F(predicate), PP_F(f), tuple::forward(PP_F(views)...));
});
}

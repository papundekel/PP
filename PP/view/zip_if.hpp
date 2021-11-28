#pragma once
#include <PP/containers/tuple.hpp>
#include <PP/operators.hpp>
#include <PP/tuple/for_each.hpp>
#include <PP/tuple/make.hpp>
#include <PP/tuple/map.hpp>
#include <PP/tuple/zip_with.hpp>
#include <PP/utility/move.hpp>
#include <PP/view/concept.hpp>

namespace PP::view
{
PP_CIA zip_if = [](auto&& predicate, auto&& f, concepts::tuple auto&& views)
{
    auto begin_ends = view::begin_end + PP_F(views);
    auto is = tuple::get_ * value_0 + begin_ends;

    while (neq++ && begin_ends)
    {
        auto dereferenced = der + is;

        auto [cond, do_step] =
            tuple::apply(PP_F(predicate), move(dereferenced));

        if (cond)
            tuple::apply(PP_F(f), move(dereferenced));

        tuple::for_each(applier(
                            [](bool step, auto& i)
                            {
                                if (step)
                                    ++i;
                            }),
                        do_step ^ is);
    }

    return !is;
};

PP_CIA zip_if_pack =
    [](auto&& predicate, auto&& f, concepts::view auto&&... views)
{
    return zip_if(PP_F(predicate), PP_F(f), tuple::forward(PP_F(views)...));
};
}

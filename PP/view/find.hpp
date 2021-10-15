#pragma once
#include "concept.hpp"

namespace PP
{
PP_CIA view_find = [](auto&& predicate, concepts::view auto&& v)
{
    auto i = view::begin_(PP_F(v));

    for (; i != view::end_(PP_F(v)) && !PP_F(predicate)(*i); ++i)
        ;

    return move(i);
};
}

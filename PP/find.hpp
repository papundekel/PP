#pragma once
#include <PP/view/concept.hpp>

namespace PP
{
constexpr auto find(concepts::view auto&& v, auto&& p)
{
    auto i = view::begin_(v);
    for (; i != view::end_(v) && !PP_F(p)(*i); ++i)
        ;
    return i;
}
}

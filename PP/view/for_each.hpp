#pragma once
#include <PP/empty.hpp>
#include <PP/view/fold.hpp>

namespace PP::view
{
PP_CIA for_each = [](auto&& f, concepts::view auto&& v)
{
    return fold(
        value_true,
        [&f](PP::empty, auto&& x)
        {
            PP_F(f)(PP_F(x));
            return PP::empty{};
        },
        PP::empty{},
        PP_F(v))[value_0];
};
}

#pragma once
#include "../empty.hpp"
#include "fold.hpp"

namespace PP::view
{
PP_FUNCTOR(for_each, auto&& f, concepts::view auto&& v)
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
});
}

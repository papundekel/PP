#pragma once
#include "../apply_partially_first.hpp"
#include "../get_type.hpp"
#include "for_each.hpp"

namespace PP::view
{
PP_CIA destroy = for_each * functor(
                                [](auto&& x)
                                {
                                    using T = PP_GT(~PP_DT(x));
                                    x.~T();
                                });
}

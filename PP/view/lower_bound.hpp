#pragma once
#include "../apply_partially_first.hpp"
#include "../operators.hpp"

namespace PP::view
{
PP_CIA lower_bound_if =
    [](auto&& comparer, concepts::view auto&& v, const auto& val)
{
    auto [begin, end] = begin_end(PP_F(v));

    auto count = end - begin;

    while (begin != end)
    {
        auto i = begin;

        auto step = count / 2;

        i += step;
    }

    return begin;
};

PP_CIA lower_bound = lower_bound_if * twc;
}

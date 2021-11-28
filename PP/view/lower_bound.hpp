#pragma once
#include <PP/containers/tuple.hpp>
#include <PP/containers/tuple_std.hpp>
#include <PP/operators.hpp>
#include <PP/pack/any.hpp>
#include <PP/partial_.hpp>
#include <PP/view/concept.hpp>

#include <compare>

namespace PP::detail
{
auto default_construct_ordering(concepts::type auto&& ordering_type)
{
    if constexpr (pack::any(eql * PP_CT(ordering_type),
                            type<std::strong_ordering>,
                            type<std::weak_ordering>,
                            type<std::partial_ordering>))
        return std::strong_ordering::less;
    else
        return construct_pack(PP_F(ordering_type));
}
}

namespace PP::view
{
PP_CIA lower_bound_if =
    [](auto&& comparer, concepts::view auto&& v, const auto& val)
{
    auto [begin, end] = begin_end(PP_F(v));

    auto count = end - begin;

    auto right_edge_comparison =
        detail::default_construct_ordering(PP_DT(PP_F(comparer)(*begin, val)));

    while (count > 0)
    {
        auto step = count / 2;

        auto i = begin;
        i += step;

        auto comparison = PP_F(comparer)(*i, val);

        if (comparison < 0)
        {
            begin = ++i;
            count -= step + 1;
        }
        else
        {
            right_edge_comparison = comparison;
            count = step;
        }
    }

    return tuple::make(begin, right_edge_comparison);
};

PP_CIA lower_bound = lower_bound_if * twc;
}

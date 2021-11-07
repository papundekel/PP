#pragma once
#include "subsequence.hpp"

namespace PP::view
{
PP_CIA subsequence_compare_if =
    [](auto&& comparer, concepts::view auto&& a, concepts::view auto&& b)
{
    auto a_b = subsequence_if(PP_F(comparer), PP_F(a), PP_F(b));
    switch (a_b)
    {
        case PP::subsequence_type::proper:
            return std::partial_ordering::less;
        case PP::subsequence_type::equal:
            return std::partial_ordering::equivalent;
        default:
            [[fallthrough]];
        case PP::subsequence_type::none:
            auto b_a = subsequence_if(PP_F(comparer), PP_F(b), PP_F(a));
            switch (b_a)
            {
                case PP::subsequence_type::proper:
                    return std::partial_ordering::greater;
                case PP::subsequence_type::equal:
                    [[fallthrough]];
                default:
                    [[fallthrough]];
                case PP::subsequence_type::none:
                    return std::partial_ordering::unordered;
            }
    }
};

PP_CIA subsequence_compare = subsequence_compare_if * eql;
}

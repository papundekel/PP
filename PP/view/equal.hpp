#pragma once
#include "../operators.hpp"
#include "first_equal.hpp"
#include "zip_iterator_std.hpp"

namespace PP
{
PP_CIA view_equal_if =
    [](auto&& comparer, concepts::view auto&& a, concepts::view auto&& b)
{
    auto [a_end, b_end] =
        view_first_difference_if(PP_F(comparer), PP_F(a), PP_F(b));

    return a_end == view::end_(PP_F(a)) && b_end == view::end_(PP_F(b));
};

PP_CIA view_equal = view_equal_if * eql;
}

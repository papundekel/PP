#pragma once
#include <PP/view/first_equal.hpp>

namespace PP::view
{
PP_CIA prefix = [](concepts::view auto&& v, concepts::view auto&& prefix)
{
    return first_difference(PP_F(v), PP_F(prefix))[value_1] ==
           view::end_(PP_F(prefix));
};
}

#pragma once
#include "view/first_equal.hpp"

namespace PP
{
PP_CIA view_prefix = [](concepts::view auto&& v, concepts::view auto&& prefix)
{
    return view_first_difference(PP_F(v), PP_F(prefix))[value_1] ==
           view::end_(PP_F(prefix));
};
}

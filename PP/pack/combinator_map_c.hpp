#pragma once
#include "../combine_c.hpp"
#include "../compose.hpp"
#include "get.hpp"
#include "map_c.hpp"

namespace PP::pack
{
// combinator_map(combinator, p)(e...) = combinator(p * e...)
PP_CIA combinator_map_c =
    combine_c(map_c)(get_0, compose(partial_first_c, get_1));
}

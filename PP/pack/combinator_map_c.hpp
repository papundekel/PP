#pragma once
#include <PP/combine_c.hpp>
#include <PP/compose.hpp>
#include <PP/partial_first_c.hpp>
#include <PP/pack/get.hpp>
#include <PP/pack/map_c.hpp>

namespace PP::pack
{
// combinator_map(combinator, p)(e...) = combinator(p * e...)
PP_CIA combinator_map_c =
    combine_c(map_c)(get_0, compose(partial_first_c, get_1));
}

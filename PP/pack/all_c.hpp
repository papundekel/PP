#pragma once
#include <PP/partial_first_c.hpp>
#include <PP/pack/combinator_and_l.hpp>
#include <PP/pack/combinator_map_c.hpp>

namespace PP::pack
{
PP_CIA all_c = partial_first_c(combinator_map_c)(combinator_and_l);
}

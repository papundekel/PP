#pragma once
#include <PP/partial_first_c.hpp>
#include <PP/pack/combinator_map_c.hpp>
#include <PP/pack/combinator_or_l.hpp>

namespace PP::pack
{
PP_CIA any_c = partial_first_c(combinator_map_c)(combinator_or_l);
}

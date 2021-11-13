#pragma once
#include "../partial_first_c.hpp"
#include "combinator_and_l.hpp"
#include "combinator_map_c.hpp"

namespace PP::pack
{
PP_CIA all_c = partial_first_c(combinator_map_c)(combinator_and_l);
}

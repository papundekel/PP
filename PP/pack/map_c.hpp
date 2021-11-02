#pragma once
#include "../partial_c.hpp"
#include "map.hpp"

namespace PP::pack
{
// map_c(packer, f)(e...) = packer(f(e)...)
PP_CIA map_c = partial_first_c(map);
}

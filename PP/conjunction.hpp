#pragma once
#include "combine_meta_c.hpp"
#include "pack/combinator_and_l.hpp"

namespace PP
{
// conjunction(f...)(a...) = true && ... && f(a...)
PP_CIA conjunction = combine_meta_c(pack::combinator_and_l);
}

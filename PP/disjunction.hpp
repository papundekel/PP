#pragma once
#include "combine_meta_c.hpp"
#include "pack/combinator_or_l.hpp"

namespace PP
{
// disjunction(f...)(a...) = false || ... || f(a...)
PP_CIA disjunction = combine_meta_c(pack::combinator_or_l);
}

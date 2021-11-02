#pragma once
#include "combine_meta_c.hpp"
#include "compose.hpp"
#include "pack/combinator_f_c.hpp"

namespace PP
{
// combine_c(c)(f...)(a...) = c(f(a...)...)
PP_CIA combine_c = compose(combine_meta_c, pack::combinator_f_c);
}

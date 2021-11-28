#pragma once
#include <PP/combine_meta_c.hpp>
#include <PP/compose.hpp>
#include <PP/pack/combinator_f_c.hpp>

namespace PP
{
// combine_c(c)(f...)(a...) = c(f(a...)...)
PP_CIA combine_c = compose(combine_meta_c, pack::combinator_f_c);
}

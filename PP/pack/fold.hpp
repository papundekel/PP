#pragma once
#include <PP/combine_c.hpp>
#include <PP/constant.hpp>
#include <PP/partial_.hpp>
#include <PP/pack/fold_init.hpp>
#include <PP/pack/get.hpp>

namespace PP::pack
{
// fold(value_true , f, i)(e#0 ... e#n) = f(...f(i, e#0), ...), e#n)
// fold(value_false, f, i)(e#0 ... e#n) = f(e#0, ... f(e#n, i) ... )
PP_CIA fold = combine_c(fold_init)(get_0, get_1, compose(constant, get_2));

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;
}

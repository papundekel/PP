#pragma once
#include "../combine_c.hpp"
#include "../constant.hpp"
#include "../partial_.hpp"
#include "fold_init.hpp"
#include "get.hpp"

namespace PP::pack
{
PP_CIA fold = combine_c(fold_init)(get_0, get_1, compose(constant, get_2));

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;
}

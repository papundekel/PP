#pragma once
#include "../combine.hpp"
#include "../compose_many.hpp"
#include "fold_init.hpp"

namespace PP::tuple
{
PP_CIA fold = combine(fold_init,
                      pack::get_0,
                      pack::get_1,
                      compose_many(constant, wrap_forward, pack::get_2),
                      pack::get_3);

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;
}

#pragma once
#include "../combine.hpp"
#include "../compose_many.hpp"
#include "fold_init.hpp"

namespace PP::tuple
{
PP_CIA fold = combine(fold_init,
                      get_0,
                      get_1,
                      compose_many(constant, wrap_forward, get_2),
                      get_3);

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;
}

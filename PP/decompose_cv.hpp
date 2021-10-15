#pragma once
#include "decompose_const.hpp"
#include "decompose_pair.hpp"
#include "decompose_pair_std.hpp"
#include "decompose_volatile.hpp"
#include "get_value.hpp"

namespace PP
{
PP_CIA decompose_cv = [](concepts::type auto t)
{
    auto [t_no_c, c] = decompose_const(t);
    auto [t_no_cv, v] = decompose_volatile(t_no_c);

    return make_decompose_pair(t_no_cv, c | v);
};
}

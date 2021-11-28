#pragma once
#include <PP/combine_c.hpp>
#include <PP/compose.hpp>
#include <PP/partial_c.hpp>
#include <PP/pack/get.hpp>
#include <PP/pack/map_c.hpp>

namespace PP::pack
{
// map_cc(packer, map)(args1...)(args2...) = packer(args1...)(map(args2)...)
PP_CIA map_cc =
    combine_c(compose)(compose(partial_last_c(map_c), get_1), get_0);
}

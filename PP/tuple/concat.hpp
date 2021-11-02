#pragma once
#include "../combine.hpp"
#include "../constant.hpp"
#include "../construct_pack.hpp"
#include "../operators.hpp"
#include "../pack/get.hpp"
#include "../pack/select.hpp"
#include "../partial_.hpp"
#include "empty.hpp"
#include "fold.hpp"
#include "make.hpp"
#include "map.hpp"
#include "prepend.hpp"

namespace PP::tuple
{
PP_CIA concat_pack = combine([](concepts::tuple auto&&, auto&&...) {},
                             apply,
                             pack::select_0*(partial_last* forward),
                             pack::get_0);

PP_CIA concat =
    combine_constrained([](concepts::tuple auto&&, concepts::tuple auto&&) {},
                        apply,
                        partial_first* concat_pack,
                        pack::get_1);

PP_CIA concats =
    combine(foldl, constant(concat), constant(tuple_empty{}), id_forward);

PP_CIA concats_pack = compose(concats, forward);
}

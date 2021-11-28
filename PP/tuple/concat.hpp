#pragma once
#include <PP/combine.hpp>
#include <PP/constant.hpp>
#include <PP/construct_pack.hpp>
#include <PP/operators.hpp>
#include <PP/pack/get.hpp>
#include <PP/pack/select.hpp>
#include <PP/partial_.hpp>
#include <PP/empty.hpp>
#include <PP/tuple/fold.hpp>
#include <PP/tuple/make.hpp>
#include <PP/tuple/map.hpp>
#include <PP/tuple/prepend.hpp>

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

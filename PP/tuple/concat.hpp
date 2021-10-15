#pragma once
#include "../apply_partially_first.hpp"
#include "../combine.hpp"
#include "../constant.hpp"
#include "../construct_pack.hpp"
#include "../operators.hpp"
#include "empty.hpp"
#include "fold.hpp"
#include "make.hpp"
#include "map.hpp"
#include "prepend.hpp"

namespace PP::tuple
{
PP_CIA concat = combine(
    apply_pack,
    constant(forward),
    apply_partially_first(apply_partially_first,
                          [](auto&& l, auto&& r, auto&& i) -> decltype(auto)
                          {
                              auto lc = count_value_t(PP_F(l));

                              if constexpr (PP_GV(i) < PP_GV(lc))
                                  return PP_F(l)[PP_F(i)];
                              else
                                  return PP_F(r)[PP_F(i) - lc];
                          }),
    compose(compose(value_sequence_make, pls++), map_pack* count_value_t));

PP_CIA concats =
    combine(foldl, constant(concat), constant(tuple_empty{}), id_forward);

PP_CIA concats_pack = compose(concats, forward);
}

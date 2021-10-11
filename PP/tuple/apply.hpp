#pragma once
#include "../apply_pack.hpp"
#include "../functor.hpp"
#include "../utility/forward.hpp"
#include "../value_t.hpp"
#include "concept.hpp"
#include "count.hpp"
#include "get.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
namespace functors
{
PP_CIA apply = [](auto&& f, concepts::tuple auto&& t) -> decltype(auto)
{
    return apply_pack(
        PP_F(f),
        [tt = PP_FW(t)](concepts::value auto&& i) -> decltype(auto)
        {
            return tt-- [PP_F(i)];
        },
        value_sequence_for(PP_F(t)));
};
}
PP_FUNCTOR(apply)
}

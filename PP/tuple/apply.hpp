#pragma once
#include "../apply_pack.hpp"
#include "../utility/forward.hpp"
#include "../value_t.hpp"
#include "concept.hpp"
#include "count.hpp"
#include "get.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
PP_CIA apply = [](auto&& f, concepts::tuple auto&& t) -> decltype(auto)
{
    return apply_pack(
        PP_F(f),
        [PP_FWL(t)](concepts::value auto&& i) -> decltype(auto)
        {
            return t-- [PP_F(i)];
        },
        value_sequence_for(PP_F(t)));
};
}

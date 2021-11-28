#pragma once
#include <PP/apply_pack.hpp>
#include <PP/utility/forward.hpp>
#include <PP/value_t.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/tuple/value_sequence_for.hpp>

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

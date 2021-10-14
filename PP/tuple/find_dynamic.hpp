#pragma once
#include "../size_t.hpp"
#include "../utility/move.hpp"
#include "find_index_state.hpp"
#include "fold.hpp"

namespace PP::tuple
{
PP_CIA find_dynamic = [](auto&& predicate, concepts::tuple auto&& tuple)
{
    return foldl(
               [PP_FWL(predicate)](
                   detail::tuple_find_index_state state,
                   auto&& element) -> detail::tuple_find_index_state
               {
                   if (state.found || predicate(PP_F(element)))
                       return {state.index, true};
                   else
                       return {state.index + 1, false};
               },
               detail::tuple_find_index_state{0, false},
               PP_F(tuple))
        .index;
};
}

#pragma once
#include "../containers/tuple.hpp"
#include "../forward_wrap.hpp"
#include "../get_value.hpp"
#include "../type_t.hpp"
#include "empty.hpp"
#include "fold.hpp"
#include "make.hpp"
#include "prepend.hpp"
#include "zip_indices.hpp"

namespace PP::tuple
{
PP_CIA splits = [](auto&& p, concepts::tuple auto&& t)
{
    return foldr(
        [PP_FWL(p)](auto&& element, auto splits)
        {
            if constexpr (PP_GV(p(PP_F(element))))
                return !prepend(tuple_empty{}, move(splits));
            else
                return [PP_FWL(element)](concepts::value auto&& i, auto split)
                {
                    if constexpr (PP_GV(i) == 0)
                        return prepend(element--, move(split));
                    else
                        return move(split);
                } +++zip_indices(move(splits));
        },
        make(tuple_empty{}),
        PP_F(t));
};
}

#pragma once
#include "../forward_wrap.hpp"
#include "../get_value.hpp"
#include "empty.hpp"
#include "fold.hpp"
#include "make.hpp"
#include "prepend.hpp"

namespace PP::tuple
{
PP_CIA filter = [](auto&& predicate, concepts::tuple auto&& t)
{
    return foldr(
        [PP_FWL(predicate)](auto&& element, concepts::tuple auto tail)
        {
            if constexpr (PP_GV(predicate(PP_F(element))))
                return !prepend(PP_F(element), move(tail));
            else
                return tail;
        },
        tuple_empty{},
        PP_F(t));
};
}

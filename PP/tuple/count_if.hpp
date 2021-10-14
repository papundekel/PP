#pragma once
#include "../size_t.hpp"
#include "fold.hpp"

namespace PP::tuple
{
PP_CIA count_if = [](auto&& p, concepts::tuple auto&& t)
{
    return foldl(
        [PP_FWL(p)](auto counter, auto&& element)
        {
            return p(PP_F(element)) ? counter + 1 : counter;
        },
        0_z,
        PP_F(t));
};
}

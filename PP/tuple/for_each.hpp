#pragma once
#include "../compose.hpp"
#include "../empty.hpp"
#include "../forward_wrap.hpp"
#include "../partial_.hpp"
#include "fold.hpp"

namespace PP::tuple
{
PP_CIA for_each_dir =
    [](concepts::value auto&& left, auto&& f, concepts::tuple auto&& t)
{
    fold(
        PP_F(left),
        [PP_FWL(f)](empty, auto&& element)
        {
            f(PP_F(element));
            return empty{};
        },
        empty{},
        PP_F(t));
};

PP_CIA for_each = for_each_dir * value_true;
}

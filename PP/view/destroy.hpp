#pragma once
#include "apply_partially_first.hpp"
#include "get_type.hpp"
#include "view/for_each.hpp"

namespace PP
{
constexpr inline auto view_destroy =
    view_for_each * functor(
                        [](auto&& x)
                        {
	                        using T = PP_GT(~PP_DT(x));
	                        x.~T();
                        });
}

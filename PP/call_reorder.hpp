#pragma once
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"

namespace PP
{
PP_CIA call_reorder = [](auto&& f)
{
    return [PP_FL(f)](auto&&... second)
    {
        return [f, ... PP_FL(second)](auto&&... first) -> decltype(auto)
        {
            return unwrap_forward(f)(PP_F(first)...)(unwrap_forward(second)...);
        };
    };
};
}

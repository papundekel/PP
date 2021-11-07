#pragma once
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"

namespace PP
{
PP_CIA call_reorder = [](auto&& f)
{
    return [PP_FL(f)](auto&&... second)
    {
        return [PP_UL(f), ... PP_FL(second)](auto&&... first) -> decltype(auto)
        {
            return unforward(f)(PP_F(first)...)(unforward(second)...);
        };
    };
};
}

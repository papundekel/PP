#pragma once
#include "call_reorder.hpp"
#include "compose.hpp"
#include "forward_wrap.hpp"
#include "pack/map_c.hpp"

namespace PP
{
PP_CIA partial_c = [](auto&& f)
{
    return [PP_FL(f)](auto&&... first)
    {
        return [PP_UL(f), ... PP_FL(first)](auto&&... last)
        {
            // TODO: missing constraint, causes internal compiler error
            return [PP_UL(f), ... PP_UL(first), ... PP_FL(last)](
                       auto&&... args) -> decltype(auto)
            {
                return unforward(
                    f)(unforward(first)..., PP_F(args)..., unforward(last)...);
            };
        };
    };
};

PP_CIA partial_first_c =

[](auto&& f)
{
    return [PP_FL(f)](auto&&... first)
    {
        return [PP_UL(f), ... PP_FL(first)](auto&&... args) -> decltype(auto)
            {
                return unforward(f)(unforward(first)..., PP_F(args)...);
            };
    };
};

PP_CIA partial_last_c = call_reorder(partial_c)();
}

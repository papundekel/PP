#pragma once
#include "call_reorder.hpp"
#include "compose.hpp"
#include "forward_wrap.hpp"

namespace PP
{
PP_CIA partial_c = [](auto&& f)
{
    return [PP_FL(f)](auto&&... first)
    {
        return [f, ... PP_FL(first)](auto&&... last)
        {
            // TODO: missing constraint, causes internal compiler error
            return
                [f, first..., ... PP_FL(last)](auto&&... args) -> decltype(auto)
            {
                return unwrap_forward(f)(unwrap_forward(first)...,
                                         PP_F(args)...,
                                         unwrap_forward(last)...);
            };
        };
    };
};

PP_CIA partial_first_c = call_reorder(compose(call_reorder, partial_c));
PP_CIA partial_last_c = call_reorder(partial_c)();
}

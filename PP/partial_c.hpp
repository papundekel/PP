#pragma once
#include <PP/forward_wrap.hpp>

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
                return backward(
                    f)(backward(first)..., PP_F(args)..., backward(last)...);
            };
        };
    };
};
}

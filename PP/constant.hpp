#pragma once
#include "forward_wrap.hpp"
#include "overloaded.hpp"

namespace PP
{
PP_CIA constant = [](auto&& c)
{
    return [PP_FL(c)](auto&&...) -> decltype(auto)
    {
        return overloaded(
            []<typename T>(const forward_wrap<T>& x) -> auto&&
            {
                return x--;
            },
            [](auto&& x)
            {
                return PP_F(x);
            })(c);
    };
};
}

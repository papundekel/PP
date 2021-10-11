#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "overloaded.hpp"

namespace PP
{
namespace functors
{
PP_CIA constant = [](auto&& cc)
{
    return [c = PP_F(cc)](auto&&...) -> decltype(auto)
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
PP_FUNCTOR(constant)
}

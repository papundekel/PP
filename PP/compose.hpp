#pragma once
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"

namespace PP
{
PP_CIA compose = [](auto&& f, auto&& g)
{
    return [ PP_FL(f),
             PP_FL(g) ](auto&&... args) -> decltype(auto) requires requires
    {
        ::PP::unwrap_forward(PP_F(f))(
            ::PP::unwrap_forward(PP_F(g))(PP_F(args)...));
    }
    {
        return unwrap_forward(f)(unwrap_forward(g)(PP_F(args)...));
    };
};
}

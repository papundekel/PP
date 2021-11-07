#pragma once
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"

namespace PP
{
PP_CIA compose = [](auto&& f, auto&& g)
{
    // clang-format off
    return [PP_FL(f), PP_FL(g)](auto&&... args) -> decltype(auto)
               requires requires
               {
                   ::PP::unforward(PP_F(f))(
                       ::PP::unforward(PP_F(g))(PP_F(args)...));
               }
           {
               return unforward(f)(unforward(g)(PP_F(args)...));
           };
    // clang-format on
};
}

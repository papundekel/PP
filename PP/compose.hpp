#pragma once
#include <PP/declval_impl.hpp>
#include <PP/forward_wrap.hpp>
#include <PP/macros/CIA.hpp>

namespace PP
{
PP_CIA compose = [](auto&& f, auto&& g)
{
    // clang-format off
    return [PP_FL(f), PP_FL(g)](auto&&... args) -> decltype(auto)
               requires requires
               {
                   ::PP::backward(PP_F(f))(
                       ::PP::backward(PP_F(g))(PP_F(args)...));
               }
           {
               return backward(f)(backward(g)(PP_F(args)...));
           };
    // clang-format on
};
}

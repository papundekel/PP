#pragma once
#include "apply_partially_first.hpp"
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
#include "noop.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_CIA combine_constrained = [](auto&& constraint, auto&& c, auto&&... f)
{
    // clang-format off
    return [PP_FL(c), ...PP_FL(f)](auto&&... args) -> decltype(auto)
               requires requires
               {
                   PP_F(constraint)(PP_F(args)...);
                   ::PP::unwrap_forward(c)(
                       ::PP::unwrap_forward(f)(PP_F(args)...)...);
               }
           {
               return unwrap_forward(c)(unwrap_forward(f)(PP_F(args)...)...);
           };
    // clang-format on
};

PP_CIA combine = combine_constrained * noop;
}

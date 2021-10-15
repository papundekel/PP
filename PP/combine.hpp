#pragma once
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_CIA combine = [](auto&& c, auto&&... f)
{
    return [PP_FL(c), ... PP_FL(f)](auto&&... args) -> decltype(auto)
    {
        return unwrap_forward(c)(unwrap_forward(f)(PP_F(args)...)...);
    };
};
}

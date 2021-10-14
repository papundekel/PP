#pragma once
#include "forward_wrap.hpp"
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
#include "utility/forward.hpp"

namespace PP
{
namespace functors
{
PP_CIA combine = [](auto&& cc, auto&&... ff)
{
    return [c = PP_F(cc), ... f = PP_F(ff)](auto&&... args) -> decltype(auto)
    {
        return unwrap_forward(c)(unwrap_forward(f)(PP_F(args)...)...);
    };
};
}
PP_FUNCTOR(combine)
}

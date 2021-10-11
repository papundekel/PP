#pragma once
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "functor_or_wrap.hpp"
#include "macros/CIA.hpp"

namespace PP
{
namespace functors
{
PP_CIA compose = [](auto&& ff, auto&& gg)
{
    return [ f = PP_F(ff),
             g = PP_F(gg) ](auto&&... args) -> decltype(auto) requires requires
    {
        ::PP::unwrap_forward(PP_F(ff))(
            ::PP::unwrap_forward(PP_F(gg))(PP_F(args)...));
    }
    {
        return unwrap_forward(f)(unwrap_forward(g)(PP_F(args)...));
    };
};
}
PP_FUNCTOR(compose)
}

constexpr auto operator|(PP::concepts::functor_or_wrap auto&& f,
                         PP::concepts::functor_or_wrap auto&& g)
{
    return PP::compose(PP_F(f), PP_F(g));
}

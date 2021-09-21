#pragma once
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "wrap.hpp"

namespace PP
{
PP_FUNCTOR(compose, auto&& ff, auto&& gg)
{
    return functor(
        [ f = PP_F(ff),
          g = PP_F(gg) ](auto&&... args) -> decltype(auto) requires requires
        {
            ::PP::unwrap_forward(PP_F(ff))(
                ::PP::unwrap_forward(PP_F(gg))(PP_F(args)...));
        }
        {
            return unwrap_forward(f)(unwrap_forward(g)(PP_F(args)...));
        });
});
}

constexpr auto operator|(PP::concepts::wrap auto&& f,
                         PP::concepts::wrap auto&& g)
{
    return PP::compose(PP_UF(f), PP_UF(g));
}

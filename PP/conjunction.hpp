#pragma once
#include "functor_or_wrap.hpp"

namespace PP
{
namespace functors
{
PP_CIA conjunction = [](auto&& f, auto&& g)
{
    return [ f = PP_F(f),
             g = PP_F(g) ](auto&&... args) -> decltype(auto) requires requires
    {
        ::PP::unwrap_forward(f)(PP_F(args)...);
        ::PP::unwrap_forward(g)(PP_F(args)...);
    }
    {
        return PP::unwrap_forward(f)(PP_F(args)...) &&
               PP::unwrap_forward(g)(PP_F(args)...);
    };
};
}
PP_FUNCTOR(conjunction)
}

constexpr auto operator&&(PP::concepts::functor_or_wrap auto&& f,
                          PP::concepts::functor_or_wrap auto&& g)
{
    return PP::conjunction(PP_F(f), PP_F(g));
}

#pragma once
#include "functor_or_wrap.hpp"

constexpr auto operator||(PP::concepts::functor_or_wrap auto&& f,
                          PP::concepts::functor_or_wrap auto&& g)
{
    return PP::functor(
        [f = PP::unwrap_functor(PP_F(f)),
         g = PP::unwrap_functor(PP_F(g))](auto&&... args) -> decltype(auto)
        {
        return PP::unwrap(f)(PP_F(args)...) || PP::unwrap(g)(PP_F(args)...);
        };
}

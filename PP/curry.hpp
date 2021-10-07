#pragma once
#include "functor.hpp"

namespace PP
{
PP_FUNCTOR(curry, auto&& f)
{
    return functor(
        [ff = unwrap_functor(PP_F(f))](auto&& arg)
        {
            return functor(
                [fff = ff, arg = PP_F(arg)](auto&&... args) -> decltype(auto)
                {
                    return fff(arg, PP_F(args)...);
                });
        });
});
}

constexpr auto operator~(PP::concepts::functor auto&& f)
{
    return PP::curry(PP::unwrap_functor(PP_F(f)));
}

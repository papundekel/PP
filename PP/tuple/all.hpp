#pragma once
#include "../forward_wrap.hpp"
#include "../wrap.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_FUNCTOR(all, auto&& pp, concepts::tuple auto&& t) -> decltype(auto)
{
    return functor(
        [p = PP_FW(pp)](auto&&... e) -> decltype(auto)
        {
            return (true && ... && p(PP_F(e)));
        })[PP_F(t)];
});
}

constexpr decltype(auto) operator&&(PP::concepts::functor auto&& f,
                                    PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::all(PP_UF(f), PP_F(tuple));
}

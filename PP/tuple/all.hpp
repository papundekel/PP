#pragma once
#include "../forward_wrap.hpp"
#include "../functor_or_wrap.hpp"
#include "apply.hpp"

namespace PP::tuple
{
namespace functors
{
PP_CIA all = [](auto&& pp, concepts::tuple auto&& t) -> decltype(auto)
{
    return apply(
        [p = PP_FW(pp)](auto&&... e) -> decltype(auto)
        {
            return (true && ... && p(PP_F(e)));
        },
        PP_F(t));
};
}
PP_FUNCTOR(all)
}

constexpr decltype(auto) operator&&(PP::concepts::functor auto&& f,
                                    PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::all(PP_F(f), PP_F(tuple));
}

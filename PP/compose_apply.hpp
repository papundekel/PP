#pragma once
#include "applier.hpp"
#include "compose.hpp"

namespace PP
{
PP_FUNCTOR(compose_apply, auto&& f, auto&& g)
{
    return compose(applier(unwrap_functor(PP_F(f))), unwrap_functor(PP_F(g)));
});
}

constexpr auto operator^(PP::concepts::functor auto&& f,
                         PP::concepts::functor auto&& g)
{
    return PP::compose_apply(PP::unwrap_functor(PP_F(f)),
                             PP::unwrap_functor(PP_F(g)));
}

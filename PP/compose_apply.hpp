#pragma once
#include "applier.hpp"
#include "compose.hpp"

namespace PP
{
PP_FUNCTOR(compose_apply, auto&& f, auto&& g)
{
    return compose(applier(unwrap_functor(PP_F(f))), unwrap_functor(PP_F(g)));
});

constexpr auto operator^(concepts::functor auto&& f, concepts::functor auto&& g)
{
    return compose_apply(unwrap_functor(PP_F(f)), unwrap_functor(PP_F(g)));
}
}

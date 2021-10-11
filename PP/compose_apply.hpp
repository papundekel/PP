#pragma once
#include "applier.hpp"
#include "compose.hpp"

namespace PP
{
namespace functors
{
PP_CIA compose_apply = [](auto&& f, auto&& g)
{
    return compose(applier(PP_F(f)), PP_F(g));
};
}
PP_FUNCTOR(compose_apply)
}

constexpr auto operator^(PP::concepts::functor auto&& f,
                         PP::concepts::functor auto&& g)
{
    return PP::compose_apply(PP_F(f), PP_F(g));
}

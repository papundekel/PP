#pragma once
#include <PP/applier.hpp>
#include <PP/compose.hpp>

namespace PP
{
PP_CIA compose_apply = [](auto&& f, auto&& g)
{
    return compose(applier(PP_F(f)), PP_F(g));
};
}

constexpr auto operator^(auto&& f, auto&& g)
{
    return PP::compose_apply(PP_F(f), PP_F(g));
}

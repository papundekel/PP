#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../containers/tuple.hpp"
#include "concept.hpp"

namespace PP::tuple
{
PP_CIA maker = *make;
PP_CIA forwarder = *forward;
}

constexpr auto operator!(PP::concepts::tuple auto&& t)
{
    return PP::tuple::maker(PP_F(t));
}

constexpr auto operator+(PP::concepts::tuple auto&& t) noexcept
{
    return PP::tuple::forwarder(PP_F(t));
}

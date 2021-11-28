#pragma once
#include <PP/applier.hpp>
#include <PP/containers/tuple.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/concept.hpp>

namespace PP::tuple
{
PP_CIA maker = make++;
PP_CIA forwarder = forward++;
}

constexpr auto operator!(PP::concepts::tuple auto&& t)
{
    return PP::tuple::maker(PP_F(t));
}

constexpr auto operator+(PP::concepts::tuple auto&& t) noexcept
{
    return PP::tuple::forwarder(PP_F(t));
}

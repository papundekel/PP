#pragma once
#include <PP/containers/tuple.hpp>
#include <PP/utility/forward.hpp>
#include <PP/tuple/apply.hpp>

namespace PP::tuple
{
PP_CIA prepend = [](auto&& head, concepts::tuple auto&& t)
{
    return apply(
        [&head](auto&&... elements)
        {
            return tuple::forward(PP_F(head), PP_F(elements)...);
        },
        PP_F(t));
};
}

constexpr auto operator+=(auto&& x, PP::concepts::tuple auto&& t) noexcept
{
    return PP::tuple::prepend(PP_F(x), PP_F(t));
}

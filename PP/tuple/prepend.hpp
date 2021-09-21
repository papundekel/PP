#pragma once
#include "../containers/tuple.hpp"
#include "../utility/forward.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_FUNCTOR(prepend, auto&& head, concepts::tuple auto&& t)
{
    return functor(
        [&head](auto&&... elements)
        {
            return forward_as_tuple(PP_F(head), PP_F(elements)...);
        })[PP_F(t)];
});
}

constexpr auto operator+=(auto&& x, PP::concepts::tuple auto&& t) noexcept
{
    return PP::tuple::prepend(PP_F(x), PP_F(t));
}

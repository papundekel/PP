#pragma once
#include "forward_wrap.hpp"
#include "get_value.hpp"

namespace PP
{
PP_CIA apply_partially_first = [](auto&& f, auto&&... a)
{
    return [PP_FL(f), ... PP_FL(a)](auto&&... b) -> decltype(auto)
        //requires requires { ::PP::unwrap_forward(f)(::PP::unwrap_forward(a)..., PP_F(b)...); }
    {
        return unwrap_forward(f)(unwrap_forward(a)..., PP_F(b)...);
    };
};
}

constexpr auto operator*(auto&& f, auto&& arg) noexcept
{
    return PP::apply_partially_first(PP_F(f), PP_F(arg));
}

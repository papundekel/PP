#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "functor_or_wrap.hpp"
#include "get_value.hpp"

namespace PP
{
namespace functors
{
PP_CIA apply_partially_first = [](auto&& ff, auto&&... aa)
{
    return [f = PP_F(ff), ... a = PP_F(aa)](auto&&... b) -> decltype(auto)
    {
        return unwrap_forward(f)(unwrap_forward(a)..., PP_F(b)...);
    };
};
}
PP_FUNCTOR(apply_partially_first)
}

constexpr auto operator*(PP::concepts::functor_or_wrap auto&& f,
                         auto&& arg) noexcept
{
    return PP::apply_partially_first(PP_F(f), PP_F(arg));
}

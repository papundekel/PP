#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"

namespace PP::detail
{
constexpr auto constant_helper(auto&& x) noexcept
{
    return PP_F(x);
}
template <typename T>
constexpr auto&& constant_helper(const forward_wrap<T>& x) noexcept
{
    return x--;
}
}

namespace PP
{
PP_FUNCTOR(constant, auto&& cc)
{
    return functor(
        [c = PP_F(cc)](auto&&...) -> decltype(auto)
        {
            return detail::constant_helper(c);
        });
});
}

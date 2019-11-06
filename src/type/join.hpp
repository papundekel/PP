#pragma once
#include "first.hpp"
#include "rest.hpp"

namespace detail::join
{
    constexpr auto _(type<> x, auto y)
    {
        return y;
    };
    constexpr auto _(auto x, type<> y)
    {
        return x;
    };
    template <typename T, typename... U>
    constexpr auto _(type<T> x, type<U...> y)
    {
        return t<T, U>;
    };
}

constexpr auto join = [](auto x, auto y)
{
    return detail::join::_(first(x), detail::join::_(rest(x), y));
};
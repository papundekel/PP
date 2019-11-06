#pragma once

namespace dfirst_rest
{
    template <bool f>
    constexpr auto _(type<> x)
    {
        return t<>;
    };
    template <bool f, typename T, typename... U>
    constexpr auto _(type<T, U...> x)
    {
        if constexpr (f)
            return t<T>;
        else
            return t<U...>;
    };
}
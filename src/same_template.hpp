#pragma once
#include "val.hpp"

namespace dsame_template
{
    template <template <typename...> typename T, template <typename...> typename  U>
    constexpr auto x = false;
    template <template <typename...> typename T>
    constexpr auto x<T, T> = true;

    template <template <typename...> typename T, template <typename...> typename... U>
    using y = val<(x<T, U> && ...)>;
}

template <template <typename...> typename T, template <typename...> typename... U>
struct same_template : dsame_template::y<T, U...>
{
    template <template <typename...> typename V>
    using as = dsame_template::y<T, U..., V>;
};
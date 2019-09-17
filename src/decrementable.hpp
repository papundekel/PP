#pragma once
#include "copy_constructible.hpp"
#include "implicitly_convertible.hpp"

namespace ddecrementable
{
    template <typename T>
    concept x = requires(T t)
    {
        { --t } -> T&;
    };
    template <typename T>
    concept y = requires(T t)
    {
        requires implicitly_convertible_to(typeof(t--), type<T>{});
    };
}
template <typename T>
constexpr auto decrementable_prefix(T) { return ddecrementable::x<untype<T>>; }
template <typename T>
constexpr auto decrementable_postfix(T) { return ddecrementable::y<untype<T>>; }

template <typename T>
constexpr auto decrementable(T t) { return decrementable_prefix(t) && decrementable_postfix(t); }

template <typename T>
requires decrementable_prefix(type<T>{}) && copy_constructible<T>
constexpr T operator--(T& t, int)
{
    auto copy = t;
    --t;
    return copy;
}
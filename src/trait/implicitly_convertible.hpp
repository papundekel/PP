#pragma once
namespace dimplicitly_convertible_to
{
    template <typename To>
    constexpr void f(To to) {}
    template <typename From, typename To>
    constexpr auto x = requires (From from)
    {
        f<To>(from);
    };
}
template <typename From, typename To>
constexpr auto implicitly_convertible_to = dimplicitly_convertible_to::x<From, To>;
#pragma once
#include "value_t.hpp"
namespace detail::abc
{
    template <typename To>
    constexpr void g(To to) {}
    template <typename From, typename To>
    concept x = requires (From from)
    {
        g<To>(from);
    };
}
template <typename From, typename To>
struct implicitly_convertible_to : value_t<detail::abc::x<From, To>> {};
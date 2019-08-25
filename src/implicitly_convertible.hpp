#pragma once
#include "value_t.hpp"
namespace dimplicitly_convertible_to
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
using implicitly_convertible_to = value_t<dimplicitly_convertible_to::x<From, To>>;
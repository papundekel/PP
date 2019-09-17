#pragma once
#include "val.hpp"
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
constexpr auto implicitly_convertible_to(From, To) { return dimplicitly_convertible_to::x<untype<From>, untype<To>>; }
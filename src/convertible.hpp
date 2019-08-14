#pragma once
#include "value_t.hpp"
namespace detail::convertible_to
{
    template <typename From, typename To>
    concept x = requires (const From from)
    {
        static_cast<To>(from);
    };
}
template <typename From, typename To>
struct convertible_to : value_t<detail::convertible_to::x<From, To>> {};
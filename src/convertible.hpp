#pragma once
#include "value_t.hpp"
namespace dconvertible_to
{
    template <typename From, typename To>
    concept x = requires (const From from)
    {
        static_cast<To>(from);
    };
}
template <typename From, typename To>
using convertible_to = value_t<dconvertible_to::x<From, To>>;
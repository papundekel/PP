#pragma once
#include "value_t.hpp"
#include "number.hpp"

namespace dinteger
{
    template <typename T>
    constexpr auto x() { return false; }
    template <typename T>
    requires number<T>::v
    constexpr auto x() { return static_cast<T>(1) / static_cast<T>(2) == 0; }
}

template <typename T>
using integer = value_t<dinteger::x<T>()>;
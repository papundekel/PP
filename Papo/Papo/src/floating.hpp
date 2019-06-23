#pragma once
#include "same.hpp"

namespace detail
{
    template <typename T>
    concept floating = same<float, T> || same<double, T> || same<long double, T>;
}

template <typename T>
concept floating = detail::floating<T>;
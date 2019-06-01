#pragma once
#include "same.hpp"
#include "remove_cv.hpp"

namespace detail
{
    template <typename T>
    concept floating = same<float, T> || same<double, T> || same<long double, T>;
}

template <typename T>
concept floating = detail::floating<remove_cv<T>>;
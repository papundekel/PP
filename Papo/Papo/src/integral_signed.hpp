#pragma once
#include "same.hpp"
#include "remove_cv.hpp"

namespace detail
{
    template <typename T>
    concept integral_signed = same<char,  T> || same<signed char, T> || same<short, T> || same<int, T> || same<long, T> || same<long long, T>;
}

template <typename T>
concept integral_signed = detail::integral_signed<T>;
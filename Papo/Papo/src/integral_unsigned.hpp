#pragma once
#include "same.hpp"
#include "remove_cv.hpp"

namespace detail
{
    template <typename T>
    concept integral_unsigned = same<unsigned char,  T> ||  same<unsigned short, T> || same<unsigned int, T> || same<unsigned long, T> || same<unsigned long long, T>;
}

template <typename T>
concept integral_unsigned = detail::integral_unsigned<remove_cv<T>>;
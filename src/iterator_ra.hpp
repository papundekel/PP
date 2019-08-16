#pragma once
#include "int.hpp"
#include "iterator_bi.hpp"
#include "ordered.hpp"

namespace detail::iterator_ra
{
    template <typename T>
    concept x = requires (T i, T j, diff_t a)
    {
        { i - j } -> diff_t;
        { i + a } -> T;
        { i - a } -> T;
    };  
}
template <typename T>
using iterator_ra = value_t<detail::iterator_ra::x<T>>;
#pragma once
#include "int.hpp"
#include "iterator_bi.hpp"
#include "ordered.hpp"

namespace diterator_ra
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
using iterator_ra = AND<iterator_bi<T>, value_t<diterator_ra::x<T>>>;
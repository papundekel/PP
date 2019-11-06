#pragma once
#include "int.hpp"
#include "iterator_bi.hpp"
#include "ordered.hpp"

namespace diterator_ra
{
    template <typename T>
    constexpr auto x = requires (T i, T j, diff_t a)
    {
        { i - j } -> diff_t;
        { i + a } -> T;
        { i - a } -> T;
    };
}
template <typename T>
constexpr auto iterator_ra = iterator_bi<T> && diterator_ra::x<T>;
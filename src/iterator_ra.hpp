#pragma once
#include "int.hpp"
#include "iterator_bi.hpp"
#include "ordered.hpp"

template <iterator_bi_c T>
concept iterator_ra_c = requires(T i, T j, diff_t a)
{
    { i - j } -> diff_t;
    { i + a } -> T;
    { i - a } -> T;
} && ordered_c<T>;
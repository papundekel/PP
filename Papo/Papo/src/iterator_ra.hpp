#pragma once
#include "int.hpp"
#include "iterator_bi.hpp"

template <typename T>
concept iterator_ra = requires(T i, T j, diff_t a)
{
    { i - j } -> diff_t;
    { i + a } -> T;
    { i - a } -> T;
} && iterator_bi<T> && ordered<T>;
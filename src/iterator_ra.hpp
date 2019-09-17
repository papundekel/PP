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
constexpr auto iterator_ra(T t) { return iterator_bi(t) && diterator_ra::x<untype<T>>; }
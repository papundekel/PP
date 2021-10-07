#pragma once
#include <tuple>

#include "../get_std.hpp"
#include "zip.hpp"

namespace std
{
template <typename... Iterators>
struct tuple_size<PP::zip_iterator<Iterators...>>
    : public tuple_size<tuple<Iterators...>>
{};
template <size_t I, typename... Iterators>
struct tuple_element<I, PP::zip_iterator<Iterators...>>
    : public tuple_element<I, tuple<Iterators...>>
{};
}

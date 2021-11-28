#pragma once
#include <PP/get_std.hpp>
#include <PP/view/zip.hpp>

#include <tuple>

namespace std
{
template <typename... Iterators>
struct tuple_size<PP::view::zip_iterator<Iterators...>>
    : public tuple_size<tuple<Iterators...>>
{};
template <size_t I, typename... Iterators>
struct tuple_element<I, PP::view::zip_iterator<Iterators...>>
    : public tuple_element<I, tuple<Iterators...>>
{};
}

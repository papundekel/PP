#pragma once
#include <tuple>

#include "../get_std.hpp"
#include "tuple.hpp"

namespace std
{
template <typename... Types>
struct tuple_size<PP::containers::tuple<Types...>>
    : public tuple_size<tuple<Types...>>
{};
template <size_t I, typename... Types>
struct tuple_element<I, PP::containers::tuple<Types...>>
    : public tuple_element<I, tuple<Types...>>
{};
}

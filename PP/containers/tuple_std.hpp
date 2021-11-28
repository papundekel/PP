#pragma once
#include <PP/get_std.hpp>
#include <PP/tuple/concept.hpp>

#include <tuple>

namespace std
{
template <typename... Types>
struct tuple_size<PP::tuple::container<Types...>>
    : public tuple_size<tuple<Types...>>
{};
template <size_t I, typename... Types>
struct tuple_element<I, PP::tuple::container<Types...>>
    : public tuple_element<I, tuple<Types...>>
{};
}

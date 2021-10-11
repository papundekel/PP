#pragma once
#include "../applier.hpp"
#include "../apply_partially_first.hpp"
#include "../compose.hpp"
#include "../containers/tuple.hpp"
#include "../overloaded.hpp"
#include "apply.hpp"
#include "get.hpp"

namespace PP::tuple
{
struct splitter_empty_tuple
{};

PP_CIA splitter = overloaded(
    [](auto&& head, auto&&... tail)
    {
        return tuple::construct(
            type_tuple<decltype(head), container<decltype(tail)...>>,
            value_false,
            PP_F(head),
            tuple::forward(PP_F(tail)...));
    },
    []()
    {
        return splitter_empty_tuple{};
    });

PP_CIA split = splitter++;

PP_CIA head = tuple_get * value_0;
PP_CIA tail = tuple_get * value_1 | split;
}

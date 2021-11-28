#pragma once
#include <PP/applier.hpp>
#include <PP/compose.hpp>
#include <PP/containers/tuple.hpp>
#include <PP/overloaded.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/get.hpp>

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

PP_CIA head = get_ * value_0;
PP_CIA tail = compose(get_ * value_1, split);
}

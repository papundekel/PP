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
PP_CIA splitter = make_overloaded_pack(
    [](auto&& head, auto&&... tail)
    {
	    return construct(
	        type_tuple<decltype(head), container<decltype(tail)...>>,
	        value_false,
	        PP_F(head),
	        forward_as_tuple(PP_F(tail)...));
    },
    []()
    {
	    return make(0, 0);
    });

PP_CIA split = *splitter;

PP_CIA head = get * value_0;
PP_CIA tail = get * value_1 | split;
}

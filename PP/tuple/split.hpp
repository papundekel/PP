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
constexpr inline auto splitter = make_overloaded_pack(
    [](auto&& head, auto&&... tail)
    {
	    return type<decltype(head), containers::tuple<decltype(tail)...>>(
	        placeholder,
	        PP_F(head),
	        forward_as_tuple(PP_F(tail)...));
    },
    []()
    {
	    return make_tuple(0, 0);
    });

constexpr inline auto split = *splitter;

constexpr inline auto head = get * value_0;
constexpr inline auto tail = get * value_1 | split;
}

#pragma once
#include <tuple>

#include "tuple.hpp"
#include "get_std.hpp"

namespace std
{
	template <typename... Types>
	struct tuple_size<PP::tuple<Types...>> : public integral_constant<size_t, sizeof...(Types)> {};
	template <std::size_t I, typename... Types>
	struct tuple_element<I, PP::tuple<Types...>> : public tuple_element<I, tuple<Types...>> {};
}

#pragma once
#include <tuple>

#include "type_tuple.hpp"
#include "get_std.hpp"

namespace std
{
	template <typename... Types>
	struct tuple_size<PP::type_tuple<Types...>> : public integral_constant<size_t, sizeof...(Types)> {};
	template <size_t I, typename... Types>
	struct tuple_element<I, PP::type_tuple<Types...>> : public tuple_element<I, std::tuple<PP::type_t<Types>...>> {};
}

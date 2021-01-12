#pragma once
#include <tuple>
#include "type_tuple.hpp"

namespace std
{
	template <typename... Types>
	struct tuple_size<PP::type_tuple<Types...>> : public integral_constant<size_t, sizeof...(Types)> {};
	template <std::size_t I, typename... Types>
	struct tuple_element<I, PP::type_tuple<Types...>> {};
	template <std::size_t I, typename T, typename... Types>
	struct tuple_element<I, PP::type_tuple<T, Types...>> : public tuple_element<I - 1, PP::type_tuple<Types...>> {};
	template <typename T, typename... Types>
	struct tuple_element<0, PP::type_tuple<T, Types...>> : public PP::type_t<PP::type_t<T>> {};
}

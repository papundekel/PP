#pragma once
#include <tuple>

#include "decompose_pair.hpp"

namespace std
{
	template <typename T, auto V>
	struct tuple_size<PP::decompose_pair<T, V>> : public integral_constant<size_t, 2> {};
	template <size_t I, typename T, auto V>
	struct tuple_element<I, PP::decompose_pair<T, V>> : public tuple_element<I, tuple<PP::type_t<T>, PP::value_t<V>>> {};
}

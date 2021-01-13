#pragma once
#include <tuple>
#include "type_t.hpp"

namespace std
{
	template <typename T>
	struct tuple_size<PP::type_t<T>> : public integral_constant<size_t, 1> {};
	template <std::size_t I, typename T>
	struct tuple_element<I, PP::type_t<T>> : public PP::type_t<PP::type_t<T>> {};
}

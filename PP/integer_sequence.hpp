#pragma once
#include <utility>
#include "value_tuple.hpp"

namespace std
{
	template <typename T, T... Values>
	constexpr decltype(auto) get(auto i, std::integer_sequence<T, Values...>)
	{
		return get(i, PP::value_tuple_v<Values...>);
	}
}

#pragma once
#include "type_t.hpp"

namespace detail
{
	template <size_t N, typename T, typename... U>
	struct nth_t : nth_t<N - 1, U...> {};

	template <typename T, typename... U>
	struct nth_t<0, T, U...> : type_t<T> {};
}

template <size_t N, typename... T>
requires N < sizeof...(T)
using nth_t = detail::nth_t<N, T...>::type;
#pragma once
#include "conditional.hpp"

template <auto val>
struct v
{
	static constexpr auto value = val;
};

namespace detail
{
	template <template <typename> typename F, size_t I, typename... T>
	struct find_t : v<I> {};

	template <template <typename> typename F, size_t I, typename T, typename... U>
	struct find_t<F, I, T, U...> : conditional<F<T>::value, v<I>, find_t<F, I + 1, U...>>::type {};
}

template <template <typename> typename F, typename... T>
constexpr size_t find_t = detail::find_t<F, 0, T...>::value;
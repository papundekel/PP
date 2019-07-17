#pragma once

namespace detail
{
	template <template <typename> typename F, size_t I, typename... T>
	constexpr size_t find_t = I;

	template <template <typename> typename F, size_t I, typename T, typename... U>
	constexpr size_t find_t<F, I, T, U...> = F<T>::value ? I : find_t<F, I + 1, U...>;
}

template <template <typename> typename F, typename... T>
constexpr size_t find_t = detail::find_t<F, 0, T...>;
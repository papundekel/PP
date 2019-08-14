#pragma once
template <template <typename...> typename T>
struct is
{
	template <typename... U>
	struct type : value_t<false> {};
	template <typename... U>
	struct type<T<U...>> : value_t<true> {};
};
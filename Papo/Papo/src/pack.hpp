#pragma once
#include "nth_t.hpp"
#include "find_t.hpp"

template <typename... T>
struct pack
{
	static constexpr auto count = sizeof...(T);

	template <size_t N>
	using get = nth_t<N, T...>;

	template <template <typename> typename Test>
	static constexpr auto find = find_t<Test, T...>;

	template <template <typename> typename Test>
	static constexpr auto contains = find<Test> != count;
};

template <typename T>
constexpr auto is_pack_v = false;

template <typename... T>
constexpr auto is_pack_v<pack<T...>> = true;

template <typename T>
struct is_pack : value_t<is_pack_v<T>> {};

template <typename T>
concept Pack = is_pack_v<T>;
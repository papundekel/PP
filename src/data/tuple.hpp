#pragma once
#include "forward.hpp"
#include "is_template.hpp"
#include "type.hpp"

template <typename... T>
struct tuple : type<T...>
{
	first data;

	constexpr tuple()
		: rest()
		, data()
	{}

	template <typename V, typename... W>
	constexpr tuple(V&& v, W&&... w)
		: rest(forward<W>(w)...)
		, data(forward<T>(v))
	{}

	template <size_t N>
	requires sizeof...(U) >= N
	constexpr auto& element()
	{
		
	}

	template <typename... V>
	using append = tuple<T, U..., V...>;
	template <typename... V>
	using prepend = tuple<V..., T, U...>;

	template <typename... V>
	struct join_helper : tuple<tuple<T, U..., V...>> {};
	template <typename... V>
	struct join_helper<tuple<V...> : join_helper<V...> {};

	template <typename... V>
	using join = join_helper<V...>::t;
};

template <typename... T>
tuple(T...) -> tuple<T...>;
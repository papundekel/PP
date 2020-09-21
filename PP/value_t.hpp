#pragma once

namespace PP
{
	template <auto V>
	struct value_t
	{
		static constexpr decltype(auto) value_f() noexcept
		{
			return V;
		}
	};

	template <auto V>
	constexpr inline value_t<V> value_v = {};

	template <auto x, auto y>
	constexpr bool operator==(value_t<x>, value_t<y>)
	{
		return x == y;
	}
}

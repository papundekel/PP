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

		constexpr operator decltype(V)() noexcept
		{
			return V;
		}

		constexpr decltype(auto) operator()() const noexcept
		{
			return V;
		}
	};
	template <auto V>
	constexpr inline value_t<V> value_v = {};

	constexpr inline value_t<0> value_0 = {};
	constexpr inline value_t<1> value_1 = {};
	constexpr inline value_t<2> value_2 = {};
	constexpr inline value_t<3> value_3 = {};
	constexpr inline value_t<4> value_4 = {};
	constexpr inline value_t<5> value_5 = {};
	constexpr inline value_t<6> value_6 = {};
	constexpr inline value_t<7> value_7 = {};
	constexpr inline value_t<8> value_8 = {};
	constexpr inline value_t<9> value_9 = {};
	
	constexpr inline value_t<true> value_true = {};
	constexpr inline value_t<false> value_false = {};

	constexpr inline value_t<nullptr> value_nullptr = {};

	template <auto x, auto y>
	constexpr auto operator<=>(value_t<x>, value_t<y>)
	{
		return x <=> y;
	}
}

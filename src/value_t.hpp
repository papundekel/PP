#pragma once

template <auto V>
struct value_t
{
	static constexpr auto v = V;
	static constexpr auto non = !V;
	
	using type = decltype(V);

	template <typename T>
	using ignore = value_t<v>;

};
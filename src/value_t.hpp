#pragma once
template <auto V>
struct value_t
{
	static constexpr auto v = V;
	
	using type = decltype(v);

	template <typename T>
	using ignore = value_t<v>;
};
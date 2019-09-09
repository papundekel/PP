#pragma once
template <auto V>
struct val
{
	static constexpr auto v = V;
	
	using type = decltype(v);

	template <typename T>
	using ignore = val<v>;
};
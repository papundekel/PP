#pragma once
template <auto V>
struct val
{
	static constexpr auto v = V;
	using type = decltype(v);
	constexpr operator type() { return v; }
    constexpr auto operator()() { return v; }
	template <typename T>
	using ignore = val<v>;
};
#pragma once

template <typename T, typename U = T>
struct pair
{
	T first;
	U second;
	constexpr pair()
		: first()
		, second()
	{}
	constexpr pair(const T& first, const U& second)
		: first(first)
		, second(second)
	{}
};
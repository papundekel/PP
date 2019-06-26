#pragma once
#include "forward.hpp"

template <typename T>
struct equals
{
	T object;

	template <typename U>
	constexpr equals(U&& object)
		: object(forward<U>(object))
	{}

	template <typename U>
	constexpr bool operator()(U&& other)
	{
		return object == forward<U>(other);
	}
};
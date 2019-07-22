#pragma once
#include "forward.hpp"
#include "remove_reference.hpp"

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
		return forward<U>(other) == object;
	}
};

template <typename U>
equals(U&&) -> equals<remove_reference<U>>;
#pragma once
#include <utility>

namespace Papo
{
	template <typename T, typename U>
	constexpr auto exchange(T& x, U&& new_value)
	{
		T old = std::move(x);
		x = std::forward<U>(new_value);
		return old;
	}
}
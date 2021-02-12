#pragma once
#include "empty_iterator.hpp"

namespace PP
{
	template <typename T>
	struct empty_view
	{
		constexpr empty_iterator<T> begin() const noexcept
		{
			return {};
		}
		constexpr empty_iterator<T> end() const noexcept
		{
			return {};
		}
	};
}
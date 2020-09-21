#pragma once
#include <type_traits>
#include "value_t.hpp"

namespace PP
{
	template <typename T>
	struct same_type
	{
		template <typename U>
		using get = value_t<std::is_same_v<T, U>>;
	};

	template <typename T, typename U>
	constexpr bool operator==(type_t<T>, type_t<U>) noexcept
	{
		return std::is_same_v<T, U>;
	}
}

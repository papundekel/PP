#pragma once
#include "type_t.hpp"

namespace PP
{
	template <typename T, typename U>
	constexpr bool operator==(type_t<T>, type_t<U>) noexcept
	{
		return same<T, U>;
	}
}

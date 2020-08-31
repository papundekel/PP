#pragma once
#include <type_traits>
#include "zip_with.hpp"

namespace PP
{
	template <view FromView, view ToView>
	constexpr void copy(FromView&& from, ToView&& to)
	{
		zip_with(
			[]<typename From, typename To>(From&& from, To&& to)
			{
				std::forward<To>(to) = std::forward<From>(from);
			},
			std::forward<FromView>(from), std::forward<ToView>(to));
	}
}

#pragma once
#include <type_traits>
#include "zip_with.hpp"

namespace PP
{
	template <view FromView, view ToView>
	constexpr void move(FromView&& from, ToView&& to)
	{
		zip_with(
			[]<typename To>(auto&& from, To&& to)
			{
				std::forward<To>(to) = std::move(from);
			},
			std::forward<FromView>(from), std::forward<ToView>(to));
	}
}

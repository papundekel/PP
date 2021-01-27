#pragma once
#include "value_t.hpp"

namespace PP
{
	template <auto f>
	constexpr inline auto concepts::valueper = []<typename T>(T) { return PP::value<f(T{})>; };
}

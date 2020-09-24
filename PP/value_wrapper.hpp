#pragma once
#include "value_t.hpp"

namespace PP
{
	template <auto f>
	constexpr inline auto value_wrapper = []<typename T>(T) { return PP::value_v<f(T{})>; };
}

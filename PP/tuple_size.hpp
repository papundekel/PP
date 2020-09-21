#pragma once
#include <tuple>

namespace PP
{
	constexpr inline auto tuple_size = [](auto&& tuple) { return std::tuple_size_v<std::remove_reference_t<decltype(tuple)>>; };
}

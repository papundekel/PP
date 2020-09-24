#pragma once
#include <tuple>

namespace PP
{
	template <typename Tuple>
	constexpr inline auto tuple_size_v = std::tuple_size_v<std::remove_reference_t<Tuple>>;

	constexpr inline auto tuple_size = [](auto&& tuple) { return tuple_size_v<decltype(tuple)>; };
}

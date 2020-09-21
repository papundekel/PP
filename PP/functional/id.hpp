#pragma once

namespace PP
{
	template <typename T>
	inline constexpr auto id = [](T t) -> decltype(auto) { return t; };

	constexpr inline auto id_weak = []<typename T>(T&& t) -> decltype(auto) { return std::forward<T>(t); };
}

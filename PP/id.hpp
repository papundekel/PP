#pragma once

namespace PP
{
	template <typename T>
	inline constexpr auto id = [](T t) -> T { return t; };
}

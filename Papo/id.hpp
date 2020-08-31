#pragma once

namespace Papo
{
	template <typename T>
	inline constexpr auto id = [](T t) -> T { return t; };
}

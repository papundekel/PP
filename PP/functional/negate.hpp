#pragma once
#include  <utility>

namespace PP
{
	constexpr inline auto negate = []<typename T>(T&& t) -> bool { return !std::forward<T>(t); };
}

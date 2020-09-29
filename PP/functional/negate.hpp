#pragma once
#include  <utility>

namespace PP
{
	constexpr inline auto negate = [](auto&& t) -> bool { return !std::forward<decltype(t)>(t); };
}

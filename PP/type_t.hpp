#pragma once

namespace PP
{
	template <typename T>
	struct type_t { using type = T; };
	template <typename T>
	constexpr inline type_t<T> type_v = {};
}

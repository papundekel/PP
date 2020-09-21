#pragma once
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto sizeof_v = []<typename T>(type_t<T>) { return sizeof(T); };
}

#pragma once
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "size_t.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto extent = make_overloaded_pack
	(
		[]<typename T, size_t N>(type_t<T[N]>) { return N; },
		[](auto t) { return size_t(0); }
	) | to_type_t;
}

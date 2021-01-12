#pragma once
#include "remove_cvref.hpp"

namespace PP
{
	constexpr inline auto tuple_size = [](auto&& tuple)
	{
		return size_implementation(remove_cvref(PP_DECLTYPE(tuple)));
	};
}

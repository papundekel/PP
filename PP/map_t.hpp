#pragma once
#include "get_type.hpp"

namespace PP
{
	template <auto map>
	struct map_t
	{
		template <typename T>
		using get = get_type<decltype(map(type_v<T>))>;
	};
}

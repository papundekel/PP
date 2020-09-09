#pragma once
#include "type_t.hpp"

namespace PP
{
	template <typename... T>
	struct type_pack
	{
		using type = type_pack<T...>;
	};
}

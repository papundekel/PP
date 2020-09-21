#pragma once
#include "type_t.hpp"
#include "get_type.hpp"

namespace PP
{
	template <typename Condition, typename True, typename False>
	using conditional = get_type<decltype([]()
		{
			if constexpr (get_value<Condition>())
				return type_t<True>{};
			else
				return type_t<False>{};
		}())>;
}

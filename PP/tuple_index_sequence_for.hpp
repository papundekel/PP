#pragma once
#include <utility>

#include "tuple_count.hpp"

namespace PP
{
	constexpr auto tuple_index_sequence_for(auto&& t)
	{
		return std::make_index_sequence<tuple_type_count(PP_DECLTYPE(t))>{};
	}
}

#pragma once
#include <utility>

#include "tuple_like.hpp"
#include "tuple_size.hpp"

namespace PP
{
	constexpr auto tuple_index_sequence_for(PP::tuple_like auto&& t)
	{
		return std::make_index_sequence<tuple_type_size(PP_DECLTYPE(t))>{};
	}
}

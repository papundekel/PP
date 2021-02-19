#pragma once
#include "tuple_count.hpp"
#include "tuple_like.hpp"
#include "tuple_zip_with.hpp"

namespace PP
{
	constexpr auto operator==(const concepts::tuple auto& a, const concepts::tuple auto& b)
	{
		return tuple_count(a) == tuple_count(b) && tuple_all(eql, a ^ b);
	}
}

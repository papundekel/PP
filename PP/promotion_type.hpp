#pragma once
#include "PP/construct_pack.hpp"
#include "PP/decl_type.hpp"
#include "PP/functional/compose.hpp"
#include "PP/overloaded.hpp"
#include "PP/type_tuple.hpp"

namespace PP
{
	constexpr inline auto get_promotion_type =
		decl_type_copy |
		make_overloaded_pack[functor([]
			(concepts::type auto t)
			{
				return [](PP_GET_TYPE(t) x) { return x; };
			}) + type_tuple<int, unsigned int, long, unsigned long, long long, unsigned long long, double, long double>] |
		construct_pack;
}

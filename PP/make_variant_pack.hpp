#pragma once
#include <variant>

#include "construct_pack.hpp"
#include "make_in_place_index.hpp"

namespace PP
{
	PP_FUNCTOR(make_variant_pack,
			   concepts::type auto	t,
			   concepts::value auto i,
			   auto&&... args)
	{
		return construct_pack(t, make_in_place_index(i), PP_FORWARD(args)...);
	});
}

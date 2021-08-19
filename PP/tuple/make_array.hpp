#pragma once
#include "../applier.hpp"
#include "../containers/array.hpp"
#include "concept.hpp"

namespace PP::tuple
{
PP_CIA maker_array = *array::make;
}

constexpr auto operator*(PP::concepts::tuple auto&& t) requires(
    !requires
    {
	    t.dont_make_array_star_operator;
    })
{
	return PP::tuple::maker_array(PP_F(t));
}

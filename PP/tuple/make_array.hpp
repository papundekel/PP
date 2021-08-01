#pragma once
#include "../applier.hpp"
#include "../containers/array.hpp"
#include "concept.hpp"

namespace PP::tuple
{
PP_CIA make_array = *make_array;
}

constexpr auto operator*(PP::concepts::tuple auto&& t) requires(
    !requires
    {
	    t.dont_make_array_star_operator;
    })
{
	return PP::tuple::make_array(PP_F(t));
}

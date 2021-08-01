#pragma once
#include "../applier.hpp"
#include "../containers/array.hpp"
#include "concept.hpp"

namespace PP::tuple
{
PP_CIA forward_array = *forward_as_array;
}

constexpr auto operator~(PP::concepts::tuple auto&& t)
{
	return PP::tuple::forward_array(PP_F(t));
}

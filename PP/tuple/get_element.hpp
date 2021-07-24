#pragma once
#include "../declval.hpp"
#include "../get_value.hpp"
#include "concept.hpp"

namespace PP::tuple
{
PP_FUNCTOR(type_get_element, concepts::value auto i, concepts::type auto t)
{
	return PP_DT(declval(t)[i]);
});
PP_FUNCTOR(get_element, concepts::value auto i, concepts::tuple auto&& t)
{
	return type_get_element(i, PP_DT(t));
});
}

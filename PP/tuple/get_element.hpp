#pragma once
#include <PP/declval.hpp>
#include <PP/get_value.hpp>
#include <PP/tuple/concept.hpp>

namespace PP::tuple
{
PP_CIA type_get_element = [](concepts::value auto&& i, concepts::type auto&& t)
{
    return PP_DT(declval(t)[i]);
};
PP_CIA get_element = [](concepts::value auto&& i, concepts::tuple auto&& t)
{
    return type_get_element(i, PP_DT(t));
};
}

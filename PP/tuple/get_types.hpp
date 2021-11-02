#pragma once
#include "../apply_pack.hpp"
#include "../containers/type_tuple.hpp"
#include "../partial.hpp"
#include "get_element.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
PP_CIA type_get_types = [](concepts::type auto&& t)
{
    return apply_pack(make_type_tuple,
                      partial(type_get_element, value_1, t),
                      type_value_sequence_for(t));
};
PP_CIA get_types = [](concepts::tuple auto&& t)
{
    return type_get_types(PP_DT(t));
};
}

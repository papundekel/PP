#pragma once
#include "../apply_pack.hpp"
#include "../apply_partially.hpp"
#include "../containers/type_tuple.hpp"
#include "get_element.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
PP_FUNCTOR(type_get_types, concepts::type auto t)
{
    return apply_pack(make_type_tuple,
                      type_get_element(partial_tag, value_1, t),
                      type_value_sequence_for(t));
});
PP_FUNCTOR(get_types, concepts::tuple auto&& t)
{
    return type_get_types(PP_DT(t));
});
}

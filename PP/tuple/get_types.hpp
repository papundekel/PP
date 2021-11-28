#pragma once
#include <PP/apply_pack.hpp>
#include <PP/containers/type_tuple.hpp>
#include <PP/partial.hpp>
#include <PP/get_element.hpp>
#include <PP/tuple/value_sequence_for.hpp>

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

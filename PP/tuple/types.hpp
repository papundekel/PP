#pragma once
#include "../apply_pack.hpp"
#include "../apply_partially.hpp"
#include "../containers/type_tuple.hpp"
#include "element.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
PP_CIA types = [](concepts::type auto&& t)
{
    return apply_pack(make_type_tuple,
                      apply_partially(type_element, value_1, t),
                      type_value_sequence_for(t));
};
}

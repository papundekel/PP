#pragma once
#include "../apply_pack.hpp"
#include "../containers/type_tuple.hpp"
#include "../partial.hpp"
#include "element.hpp"
#include "value_sequence_for.hpp"

namespace PP::tuple
{
PP_CIA types = [](concepts::type auto&& t)
{
    return apply_pack(make_type_tuple,
                      partial(type_element, value_1, t),
                      type_value_sequence_for(t));
};
}

#pragma once
#include <PP/apply_pack.hpp>
#include <PP/containers/type_tuple.hpp>
#include <PP/partial.hpp>
#include <PP/tuple/element.hpp>
#include <PP/tuple/value_sequence_for.hpp>

namespace PP::tuple
{
PP_CIA types = [](concepts::type auto&& t)
{
    return apply_pack(make_type_tuple,
                      partial(type_element, value_1, t),
                      type_value_sequence_for(t));
};
}

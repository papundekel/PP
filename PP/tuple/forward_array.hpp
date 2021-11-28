#pragma once
#include <PP/applier.hpp>
#include <PP/containers/array.hpp>
#include <PP/tuple/concept.hpp>

namespace PP::tuple
{
PP_CIA forward_array = array::forward++;
}

constexpr auto operator~(PP::concepts::tuple auto&& t)
{
    return PP::tuple::forward_array(PP_F(t));
}

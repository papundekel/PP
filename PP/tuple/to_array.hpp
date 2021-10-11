#pragma once
#include "../conditional.hpp"
#include "../containers/array.hpp"
#include "../get_type.hpp"
#include "apply.hpp"
#include "concept.hpp"
#include "count.hpp"
#include "element.hpp"

namespace PP::detail
{
constexpr auto tuple_first_element_or(concepts::type auto t,
                                      concepts::tuple auto&& tuple)
{
    if constexpr (type_count(PP_DT(tuple)) != 0)
        return element(value_0, PP_F(tuple));
    else
        return t;
}

constexpr auto tuple_to_array_helper(concepts::type auto t,
                                     concepts::tuple auto&& tuple)
{
    return conditional(value<PP_COPY_TYPE(t) == type_void>,
                       tuple_first_element_or(type_char, PP_F(tuple)),
                       t);
}
}

namespace PP::tuple
{
PP_CIA to_array = [](concepts::type auto&& t, concepts::tuple auto&& tuple)
{
    return (array::construct * PP_FW(t) * placeholder)[PP_F(tuple)];
};
}

constexpr auto operator&(PP::concepts::type auto t,
                         PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::to_array(t, PP_F(tuple));
}

constexpr auto operator&(PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::to_array(PP::type_void, PP_F(tuple));
}

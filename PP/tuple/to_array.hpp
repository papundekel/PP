#pragma once
#include <PP/conditional.hpp>
#include <PP/containers/array.hpp>
#include <PP/get_type.hpp>
#include <PP/tuple/apply.hpp>
#include <PP/tuple/concept.hpp>
#include <PP/tuple/count.hpp>
#include <PP/tuple/element.hpp>

namespace PP::detail
{
constexpr auto tuple_first_element_or(concepts::type auto&& t,
                                      concepts::tuple auto&& tuple)
{
    if constexpr (type_count(PP_DT(tuple)) != 0)
        return element(value_0, PP_F(tuple));
    else
        return t;
}

constexpr auto tuple_to_array_helper(concepts::type auto&& t,
                                     concepts::tuple auto&& tuple)
{
    return conditional(value<PP_CT(t) == type_void>,
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

constexpr auto operator&(PP::concepts::type auto&& t,
                         PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::to_array(t, PP_F(tuple));
}

constexpr auto operator&(PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::to_array(PP::type_void, PP_F(tuple));
}

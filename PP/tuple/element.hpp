#pragma once
#include <PP/copy_cv.hpp>
#include <PP/decl_type.hpp>
#include <PP/declval.hpp>
#include <PP/get_value.hpp>
#include <PP/tuple/head_element.hpp>
#include <PP/tuple/recursive.hpp>

namespace PP::detail
{
template <typename I, typename T>
concept tuple_concept_element_member = requires
{
    {
        ::PP::declval(::PP::type<T>).element(::PP::declval(::PP::type<I>))
        } -> concepts::type;
};
template <typename I, typename T>
concept tuple_concept_element_nonmember =
    tuple_concept_element_member<I, T> || requires
{
    {
        element_implementation(::PP::declval(::PP::type<I>),
                               ::PP::declval(::PP::type<T>))
        } -> concepts::type;
};
template <typename I, typename T>
concept tuple_concept_element_recursive =
    tuple_concept_element_nonmember<I, T> || requires
{
    {
        ::PP::tuple::recursive(tuple::head_element,
                               ::PP::declval(::PP::type<I>),
                               ::PP::declval(::PP::type<T>))
        } -> concepts::type;
};

constexpr auto tuple_element_helper(concepts::value auto&& i, auto&& t) requires
    tuple_concept_element_member<decltype(i), decltype(t)>
{
    return PP_F(t).element(i);
}
constexpr auto tuple_element_helper(concepts::value auto&& i, auto&& t) requires
    tuple_concept_element_nonmember<decltype(i), decltype(t)>
{
    return element_implementation(i, PP_F(t));
}
constexpr auto tuple_element_helper(concepts::value auto&& i, auto&& t) requires
    tuple_concept_element_recursive<decltype(i), decltype(t)>
{
    return ::PP::tuple::recursive(tuple::head_element, i, PP_F(t));
}
}

namespace PP::tuple
{
PP_CIA element =
    [](concepts::value auto&& i,
       auto&& t) requires detail::tuple_concept_element_recursive<decltype(i),
                                                                  decltype(t)>
{
    return copy_cv(PP_DT(t), detail::tuple_element_helper(i, PP_F(t)));
};

PP_CIA type_element = [](concepts::value auto&& i, concepts::type auto&& t)
{
    return PP_CT(element(i, declval(t)));
};
}

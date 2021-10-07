#pragma once
#include "../declval.hpp"
#include "../functor.hpp"

namespace PP::detail
{
template <typename T>
concept tuple_concept_head_no_get_member = requires
{
    declval(type<T>).head();
};
template <typename T>
concept tuple_concept_head_no_get_any =
    tuple_concept_head_no_get_member<T> || requires
{
    head_impl(declval(type<T>));
};
}

namespace PP::tuple
{
PP_FUNCTOR(head_no_get, detail::tuple_concept_head_no_get_any auto&& t)
    -> decltype(auto)
{
    if constexpr (PP::detail::tuple_concept_head_no_get_member<decltype(t)>)
        return PP_F(t).head();
    else
        return head_impl(PP_F(t));
});
}

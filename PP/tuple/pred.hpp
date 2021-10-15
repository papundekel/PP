#pragma once

namespace PP::detail
{
template <typename T>
concept tuple_concept_pred_member = requires
{
    declval(type<T>).pred();
};
template <typename T>
concept tuple_concept_pred_any = tuple_concept_pred_member<T> || requires
{
    pred_implementation(declval(type<T>));
};
}

namespace PP::tuple
{
PP_CIA pred = [](detail::tuple_concept_pred_any auto&& t) -> decltype(auto)
{
    if constexpr (detail::tuple_concept_pred_member<decltype(t)>)
        return PP_F(t).pred();
    else
        return pred_implementation(PP_F(t));
};
}

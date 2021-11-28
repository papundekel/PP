#pragma once
#include <PP/declval.hpp>
#include <PP/complete_object.hpp>
#include <PP/function.hpp>
#include <PP/reference.hpp>

namespace PP
{
PP_CIA is_destructible = [](concepts::type auto&& t)
{
    constexpr auto T = PP_CT(t);

    if constexpr (is_reference(T))
        return true;
    else if constexpr (is_complete_object(T))
    {
        using U = PP_GT(T);
        return requires
        {
            declval(type<U&>).~U();
        };
    }
    else
        return false;
};

namespace concepts
{
template <typename T>
concept destructible = is_destructible(PP::type<T>) || reference<T>;
}
}

#pragma once
#include <PP/concepts/reference.hpp>
#include <PP/reference_wrapper.hpp>

namespace PP
{
PP_CIA wrap_reference = [](concepts::type auto&& t)
{
    if constexpr (is_reference(PP_CT(t)))
        return type<reference_wrapper<PP_GT(t)>>;
    else
        return t;
};
}
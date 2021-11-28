#pragma once
#include <PP/get_value.hpp>
#include <PP/type_t.hpp>
#include <PP/utility/forward.hpp>

namespace PP::tuple
{
PP_CIA get_ =
    [](concepts::value auto&& i, auto&& t) -> decltype(auto) requires requires
{
    PP_F(t)[i];
}
{
    return PP_F(t)[i];
};
}

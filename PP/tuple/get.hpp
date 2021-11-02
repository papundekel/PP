#pragma once
#include "../get_value.hpp"
#include "../type_t.hpp"
#include "../utility/forward.hpp"

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

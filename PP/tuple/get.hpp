#pragma once
#include "../get_value.hpp"
#include "../type_t.hpp"
#include "../utility/forward.hpp"

namespace PP::tuple
{
PP_CIA get_0 = [](auto&& x, auto&&...) -> auto&&
{
    return PP_F(x);
};
PP_CIA get_1 = [](auto&&, auto&& x, auto&&...) -> auto&&
{
    return PP_F(x);
};
PP_CIA get_2 = [](auto&&, auto&&, auto&& x, auto&&...) -> auto&&
{
    return PP_F(x);
};
PP_CIA get_3 = [](auto&&, auto&&, auto&&, auto&& x, auto&&...) -> auto&&
{
    return PP_F(x);
};

PP_CIA get_ =
    [](concepts::value auto&& i, auto&& t) -> decltype(auto) requires requires
{
    PP_F(t)[i];
}
{
    return PP_F(t)[i];
};
}

#pragma once

namespace PP::pack
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
}

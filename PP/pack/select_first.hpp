#pragma once

namespace PP::pack
{
PP_CIA select_first_1 = [](auto&& f, auto&& a, auto&&...) -> decltype(auto)
{
    return PP_F(f)(PP_F(a));
};
PP_CIA select_first_2 =
    [](auto&& f, auto&& a, auto&& b, auto&&...) -> decltype(auto)
{
    return PP_F(f)(PP_F(a), PP_F(b));
};
PP_CIA select_first_3 =
    [](auto&& f, auto&& a, auto&& b, auto&& c, auto&&...) -> decltype(auto)
{
    return PP_F(f)(PP_F(a), PP_F(b), PP_F(c));
};
PP_CIA select_first_4 =
    [](auto&& f, auto&& a, auto&& b, auto&& c, auto&& d, auto&&...)
    -> decltype(auto)
{
    return PP_F(f)(PP_F(a), PP_F(b), PP_F(c), PP_F(d));
};
}

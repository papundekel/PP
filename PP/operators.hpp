#pragma once
#include "macros/CIA.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_CIA eql = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) == PP_F(y);
};
PP_CIA neq = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) != PP_F(y);
};
PP_CIA lst = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) < PP_F(y);
};
PP_CIA lte = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) <= PP_F(y);
};
PP_CIA twc = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) <=> PP_F(y);
};
PP_CIA or_ = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) || PP_F(y);
};
PP_CIA an_ = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) && PP_F(y);
};
PP_CIA pls = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) + PP_F(y);
};
PP_CIA asg = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) = PP_F(y);
};
PP_CIA pas = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) += PP_F(y);
};
PP_CIA mas = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) -= PP_F(y);
};
PP_CIA ipr = [](auto&& x) -> decltype(auto)
{
    return ++PP_F(x);
};
PP_CIA der = [](auto&& x) -> decltype(auto)
{
    return *PP_F(x);
};
PP_CIA neg = [](auto&& x) -> decltype(auto)
{
    return !PP_F(x);
};
PP_CIA cal = [](auto&& f, auto&&... args) -> decltype(auto)
{
    return PP_F(f)(PP_F(args)...);
};
}

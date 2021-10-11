#pragma once
#include "functor.hpp"
#include "macros/CIA.hpp"
#include "utility/forward.hpp"

namespace PP
{
namespace functors
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
PP_FUNCTOR(eql)
PP_FUNCTOR(neq)
PP_FUNCTOR(lst)
PP_FUNCTOR(lte)
PP_FUNCTOR(or_)
PP_FUNCTOR(an_)
PP_FUNCTOR(pls)
PP_FUNCTOR(asg)
PP_FUNCTOR(pas)
PP_FUNCTOR(mas)
PP_FUNCTOR(ipr)
PP_FUNCTOR(der)
PP_FUNCTOR(neg)
PP_FUNCTOR(cal)
}

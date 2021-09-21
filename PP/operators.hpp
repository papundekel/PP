#pragma once
#include "functor.hpp"

namespace PP
{
PP_FUNCTOR(eql, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) == PP_F(y);
});
PP_FUNCTOR(neq, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) != PP_F(y);
});
PP_FUNCTOR(lst, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) < PP_F(y);
});
PP_FUNCTOR(lte, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) <= PP_F(y);
});
PP_FUNCTOR(or_, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) || PP_F(y);
});
PP_FUNCTOR(an_, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) && PP_F(y);
});
PP_FUNCTOR(pls, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) + PP_F(y);
});
PP_FUNCTOR(asg, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) = PP_F(y);
});
PP_FUNCTOR(pas, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) += PP_F(y);
});
PP_FUNCTOR(mas, auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) -= PP_F(y);
});
PP_FUNCTOR(ipr, auto&& x) -> decltype(auto)
{
    return ++PP_F(x);
});
PP_FUNCTOR(der, auto&& x) -> decltype(auto)
{
    return *PP_F(x);
});
PP_FUNCTOR(neg, auto&& x) -> decltype(auto)
{
    return !PP_F(x);
});
PP_FUNCTOR(cal, auto&& f, auto&&... args) -> decltype(auto)
{
    return PP_F(f)(PP_F(args)...);
});
}

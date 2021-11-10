#pragma once

namespace PPtest
{
template <typename L, typename T>
struct lambda
{
    L lam;
    T val;

    lambda(L lam, T val)
        : lam(lam)
        , val(val)
    {}

    decltype(auto) operator()(auto&&... args) const
    {
        return lam(val, static_cast<decltype(args)&&>(args)...);
    }
};
}

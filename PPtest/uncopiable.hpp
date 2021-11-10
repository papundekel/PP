#pragma once

namespace PPtest
{
template <typename T>
struct uncopiable
{
    T val;

    uncopiable(T val)
        : val(val)
    {}
    uncopiable(const uncopiable&) = delete;
    uncopiable(uncopiable&) = delete;

    decltype(auto) operator()(auto&&... args) const
    {
        return val(static_cast<decltype(args)&&>(args)...);
    }
};
}

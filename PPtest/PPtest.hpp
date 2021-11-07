#pragma once
#include <iosfwd>
#include <string_view>

namespace PPtest
{
using test_function_type = void(std::ostream& out_key, std::ostream& out_run);

template <int I>
test_function_type test_function;

template <int I>
std::string_view test_function_name();

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
        return val(std::forward<decltype(args)>(args)...);
    }
};

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
        return lam(val, std::forward<decltype(args)>(args)...);
    }
};

struct counter
{
    int& x;

    counter(int& x) noexcept;
    counter(const counter& n) noexcept;
};
}

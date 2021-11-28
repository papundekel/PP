#pragma once
#include <PP/utility/forward.hpp>

// clang-format off
namespace PP
{
PP_CIA call = [](auto&& f, auto&&... args) -> decltype(auto)
    requires requires { PP_F(f)(PP_F(args)...); }
{
    return PP_F(f)(PP_F(args)...);
};

constexpr decltype(auto) operator<<=(auto&& f, auto&& arg)
    requires requires { PP_F(f)(PP_F(arg)); }
{
    return PP_F(f)(PP_F(arg));
}

constexpr decltype(auto) operator>>=(auto&& arg, auto&& f)
    requires requires { PP_F(f)(PP_F(arg)); }
{
    return PP_F(f)(PP_F(arg));
}
// clang-format on
}

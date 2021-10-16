#pragma once
#include "utility/forward.hpp"

// clang-format off
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

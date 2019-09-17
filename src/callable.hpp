#pragma once
#include "forward.hpp"
#include "implicitly_convertible.hpp"
#include "declval.hpp"
#include "val.hpp"

namespace dcallable
{
    template <typename F, typename... Args>
    concept x = requires (F f, Args... args)
    {
        f(forward<Args>(args)...);
    };
}

template <typename F, typename... Args>
constexpr auto callable(F, Args...) { return dcallable::x<untype<F>, untype<Args>...>; }

template <typename F, typename... Args>
requires callable(F{}, Args{}...)
constexpr auto return_type(F f, Args... args) { return typeof(declval(f)(declval(args)...)); }

template <typename F, typename R, typename... Args>
constexpr auto callable_r (F f, R r, Args... args)  { return callable(f, args...) && implicitly_convertible_to(return_type(f, args...), r); }
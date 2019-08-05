#pragma once
#include "forward.hpp"
#include "convertible.hpp"
#include "as_lvalue.hpp"
#include "declval.hpp"

template <typename F, typename... Args>
concept callable_c = requires (F f, Args... args)
{
    f(frwd<Args>(args)...);
};

template <typename F, typename... Args>
requires callable_c<F, Args...>
using return_t = decltype(declval<F>()(declval<Args>()...));

template <typename F, typename R, typename ...Args>
concept callable_r_c = callable_c<F, Args...> && implicitly_convertible_to_c<return_t<F, Args...>, R>;
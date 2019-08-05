#pragma once
#include "forward.hpp"
#include "convertible.hpp"
#include "as_lvalue.hpp"
#include "declval.hpp"

template <typename F, typename... Args>
concept callable = requires (F f, Args... args)
{
    f(frwd<Args>(args)...);
};

template <typename F, typename... Args>
requires callable<F, Args...>
using return_t = decltype(declval<F>()(declval<Args>()...));

template <typename F, typename R, typename ...Args>
concept callable_r = callable<F, Args...> && implicitly_convertible_to<return_t<F, Args...>, R>;
#pragma once
#include "convertible.hpp"
#include "conditional.hpp"
template <typename F, typename ...Args>
concept callable = requires (F f, Args... args)
{
    f(args...);
};

template <typename F, typename ...Args>
using return_t = decltype(declval<F>()(declval<Args>()...));

template <typename R, typename F, typename ...Args>
concept callable_r = callable<F, Args...> && convertible_to<return_t<F, Args...>, R>;
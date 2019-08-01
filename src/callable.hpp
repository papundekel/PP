#pragma once
#include "forward.hpp"
#include "convertible.hpp"

template <typename F, typename ...Args>
concept callable = requires (F f, Args... args)
{
    f(args...);
};

template <typename F, typename ...Args>
constexpr auto rt(F f, Args... args) -> decltype(f(args...));

template <typename F, typename ...Args>
using return_t = decltype(rt<F, Args...>(declval<F>(), declval<Args>()...));

template <typename F, typename R, typename ...Args>
concept callable_r = callable<F, Args...> && implicitly_convertible_to<return_t<F, Args...>, R>;
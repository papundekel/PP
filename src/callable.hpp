#pragma once
#include "forward.hpp"
#include "convertible.hpp"
#include "declval.hpp"
#include "value_t.hpp"

template <typename F, typename... Args>
concept xxx = requires (F f, Args... args)
{
    f(frwd<Args>(args)...);
};

template <typename F, typename... Args>
constexpr bool x = xxx<F, Args...>;

template <typename F, typename... Args>
using callable = value_t<x<F, Args...>>;

template <typename F, typename... Args>
requires callable<F, Args...>::v
using return_type = decltype(declval<F>()(declval<Args>()...));

template <typename F, typename R, typename... Args>
requires callable<F, Args...>::v
struct callable_r : value_t<callable<F, Args...>::v && implicitly_convertible_to<return_type<F, Args...>, R>::v> {};
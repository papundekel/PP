#pragma once
#include "forward.hpp"
#include "convertible.hpp"
#include "declval.hpp"
#include "val.hpp"

namespace dcallable
{
    template <typename F, typename... Args>
    concept x = requires (F f, Args... args)
    {
        f(frwd<Args>(args)...);
    };

    // straight concept to val causes weird error
    template <typename F, typename... Args>
    constexpr auto y = x<F, Args...>;
}

template <typename F, typename... Args>
using callable = val<dcallable::y<F, Args...>>;

template <typename F, typename... Args>
requires callable<F, Args...>::v
using return_type = decltype(declval<F>()(declval<Args>()...));

template <typename F, typename R, typename... Args>
requires callable<F, Args...>::v
struct callable_r : val<callable<F, Args...>::v && implicitly_convertible_to<return_type<F, Args...>, R>::v> {};
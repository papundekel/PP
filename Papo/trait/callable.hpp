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
constexpr auto callable = dcallable::x<F, Args...>;

template <typename F, typename... Args>
requires callable<F, Args...>
using return_type = decltype(declval<F>()(declval<Args>()...));

template <typename F, typename R, typename... Args>
constexpr auto callable_r = callable<F, Args...> && implicitly_convertible_to<return_type<F, Args...>, R>;
#pragma once
#include "id.hpp"
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
#include "overloaded.hpp"
#include "placeholder.hpp"
#include "utility/forward.hpp"

namespace PP
{
template <typename T>
class forward_wrap
{
    T&& ref;

public:
    constexpr forward_wrap(const forward_wrap& other) noexcept
        : ref(PP_F(other.ref))
    {}
    constexpr forward_wrap(placeholder_t, T&& ref) noexcept
        : ref(PP_F(ref))
    {}

    constexpr auto&& operator--(int) const noexcept
    {
        return PP_F(ref);
    }
};
template <typename T>
forward_wrap(placeholder_t, T&&) -> forward_wrap<T>;

template <typename T>
class forward_wrap_wrap
{
    T wrap;

public:
    constexpr forward_wrap_wrap(const forward_wrap_wrap& other) noexcept
        : wrap(other.wrap)
    {}
    constexpr forward_wrap_wrap(placeholder_t, T wrap) noexcept
        : wrap(wrap)
    {}

    constexpr auto operator--(int) const noexcept
    {
        return wrap;
    }
};

#define PP_FW(x) ::PP::forward_wrap(::PP::placeholder, PP_F(x))
#define PP_FWL(x) x = PP_FW(x)

PP_CIA wrap_forward = [](auto&& x)
{
    return PP_FW(x);
};

#define PP_FWW(x) ::PP::forward_wrap_wrap(::PP::placeholder, PP_FW(x))

PP_CIA wrap_wrap_forward = [](auto&& x)
{
    return PP_FWW(x);
};

PP_CIA unwrap_forward_wrap_pure = []<typename T>(forward_wrap<T> x) -> auto&&
{
    return x--;
};

PP_CIA unwrap_forward_wrap_wrap_pure = []<typename T>(forward_wrap_wrap<T> x)
{
    return x--;
};

PP_CIA unwrap_forward = overloaded(unwrap_forward_wrap_pure,
                                   unwrap_forward_wrap_wrap_pure,
                                   id_forward);

PP_CIA make_fw = [](auto&& x)
{
    return wrap_forward(unwrap_forward(PP_F(x)));
};
}

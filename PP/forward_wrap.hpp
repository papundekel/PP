#pragma once
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
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

    constexpr decltype(auto) operator--(int) const noexcept
    {
        return PP_F(ref);
    }
    constexpr decltype(auto) operator()(auto&&... args) const
    {
        return PP_F(ref)(PP_F(args)...);
    }
};
template <typename T>
forward_wrap(placeholder_t, T&&) -> forward_wrap<T>;

#define PP_FW(x) ::PP::forward_wrap(::PP::placeholder, PP_F(x))
#define PP_FWL(x) x = PP_FW(x)

PP_CIA wrap_forward = [](auto&& x)
{
    return PP_FW(x);
};

constexpr auto&& unwrap_forward(auto&& x) noexcept
{
    return PP_F(x);
}
template <typename T>
constexpr auto&& unwrap_forward(const forward_wrap<T>& x) noexcept
{
    return x--;
}

}

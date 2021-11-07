#pragma once
#include "get_value.hpp"
#include "id.hpp"
#include "macros/CIA.hpp"
#include "macros/functor.hpp"
#include "overloaded.hpp"
#include "placeholder.hpp"
#include "size_t.hpp"
#include "utility/forward.hpp"

namespace PP
{
template <size_t D, typename T>
class forward_wrap
{
    T&& ref;

    constexpr auto&& get() const noexcept
    {
        return PP_F(ref);
    }

public:
    constexpr forward_wrap(const forward_wrap& other) noexcept
        : ref(other.get())
    {}
    constexpr forward_wrap(auto&&, T&& ref) noexcept
        : ref(PP_F(ref))
    {}

    constexpr decltype(auto) operator--(int) const noexcept
    {
        if constexpr (D == 0)
            return get();
        else
            return forward_wrap<D - 1, T>(0, get());
    }
};
template <typename T>
forward_wrap(concepts::value auto&& d, T&&) -> forward_wrap<PP_GV(d), T>;

#define PP_FW(x) ::PP::forward_wrap(::PP::value_0, PP_F(x))
#define PP_FWL(x) x = PP_FW(x)

PP_CIA wrap_forward = [](auto&& x)
{
    return PP_FW(x);
};

PP_CIA unforward_pure =
    []<size_t D, typename T>(forward_wrap<D, T> x) -> decltype(auto)
{
    return x--;
};

PP_CIA unforward = overloaded(unforward_pure, id_forward);

#define PP_UL(x) x = ::PP::unforward(x)

PP_CIA make_fw = [](auto&& x)
{
    return ::PP::forward_wrap(value_0, unforward(PP_F(x)));
};

PP_CIA make_fw_d = [](concepts::value auto&& depth, auto&& x)
{
    return ::PP::forward_wrap(PP_F(depth), unforward(PP_F(x)));
};
}

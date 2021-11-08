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

public:
    constexpr forward_wrap(const forward_wrap& w) noexcept
        : ref(w--)
    {}
    constexpr forward_wrap(int, T&& ref) noexcept
        : ref(PP_F(ref))
    {}

    constexpr auto&& operator--(int) const noexcept
    {
        return PP_F(ref);
    }
};
}

namespace PP::detail
{
PP_CIA forward = overloaded(
    []<size_t D, typename T>(concepts::value auto&& depth, forward_wrap<D, T> w)
    {
        return forward_wrap<D + PP_GV(depth), T>(0, w--);
    },
    []<typename T>(concepts::value auto&& depth, T&& x)
    {
        return forward_wrap<PP_GV(depth), T>(0, PP_F(x));
    });

PP_CIA backward = overloaded(
    []<size_t D, typename T>(concepts::value auto&& depth,
                             forward_wrap<D, T> w) -> decltype(auto)
    {
        if constexpr (D <= PP_GV(depth))
            return w--;
        else
            return forward_wrap<D - PP_GV(depth), T>(0, w--);
    },
    [](concepts::value auto&&, auto&& x) -> decltype(auto)
    {
        return PP_F(x);
    });
}

namespace PP
{
PP_CIA forward = overloaded(detail::forward,
                            [](auto&& x)
                            {
                                return detail::forward(value_1, PP_F(x));
                            });

PP_CIA backward = overloaded(detail::backward,
                             [](auto&& x) -> decltype(auto)
                             {
                                 return detail::backward(value_1, PP_F(x));
                             });

#define PP_FW(x) ::PP::forward(PP_F(x))
#define PP_FWL(x) x = PP_FW(x)
#define PP_UL(x) x = ::PP::backward(x)
}

#pragma once
#include <PP/utility/forward.hpp>

namespace PP
{
template <auto V>
struct value_t
{
    static constexpr decltype(auto) value_f() noexcept
    {
        return V;
    }

    explicit constexpr operator decltype(V)() const noexcept
    {
        return V;
    }

    constexpr decltype(auto) operator()(auto&&... args) const noexcept
    {
        return V(PP_F(args)...);
    }
};
template <auto V>
constexpr inline value_t<V> value = {};

constexpr inline value_t<0u> value_0 = {};
constexpr inline value_t<1u> value_1 = {};
constexpr inline value_t<2u> value_2 = {};
constexpr inline value_t<3u> value_3 = {};
constexpr inline value_t<4u> value_4 = {};
constexpr inline value_t<5u> value_5 = {};
constexpr inline value_t<6u> value_6 = {};
constexpr inline value_t<7u> value_7 = {};
constexpr inline value_t<8u> value_8 = {};
constexpr inline value_t<9u> value_9 = {};

constexpr inline value_t<true> value_true = {};
constexpr inline value_t<false> value_false = {};

constexpr inline value_t<nullptr> value_nullptr = {};

#define PP_SIZEOF(x) (::PP::value<sizeof(x)>)
#define PP_SIZEOF___(x) (::PP::value<sizeof...(x)>)
}

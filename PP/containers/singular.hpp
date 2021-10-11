#pragma once
#include "../iterate_tuple.hpp"

namespace PP::containers
{
template <typename T>
class singular : public iterate_tuple<value_t<1>, T>
{
public:
    constexpr singular(placeholder_t, auto&& value)
        : iterate_tuple<value_t<1>, T>(placeholder, PP_F(value))
    {}
    constexpr singular(placeholder_t, concepts::type auto, auto&& value)
        : singular(placeholder, PP_F(value))
    {}
};
template <typename T>
singular(placeholder_t, T) -> singular<T>;
singular(placeholder_t, concepts::type auto t, auto&&) -> singular<PP_GT(t)>;

PP_CIA make_singular = [](auto&& x)
{
    return singular(placeholder, PP_F(x));
};

PP_CIA forward_as_singular = [](auto&& x) noexcept
{
    return singular(placeholder, PP_DT(x), PP_F(x));
};
}

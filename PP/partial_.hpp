#pragma once
#include <PP/get_value.hpp>
#include <PP/partial_c.hpp>

namespace PP
{
PP_CIA partial_ = [](concepts::value auto&& first, auto&& f, auto&&... a)
{
    auto ff = partial_c(PP_F(f));
    if constexpr (PP_GV(first))
        return ff(PP_F(a)...)();
    else
        return ff()(PP_F(a)...);
};

PP_CIA partial_first = partial_c(partial_)(value_true)();
PP_CIA partial_last = partial_c(partial_)(value_false)();
}

constexpr auto operator*(auto&& f, auto&& arg) noexcept
{
    return PP::partial_first(PP_F(f), PP_F(arg));
}

#pragma once
#include <PP/macros/CIA.hpp>
#include <PP/utility/forward.hpp>

namespace PP::pack
{
PP_CIA combinator_and_r = [](auto&&... f) -> decltype(auto)
{
    return (PP_F(f)() && ... && true);
};
}

#pragma once
#include "../macros/CIA.hpp"
#include "../utility/forward.hpp"

namespace PP::pack
{
PP_CIA combinator_and_r = [](auto&&... f) -> decltype(auto)
{
    return (PP_F(f)() && ... && true);
};
}

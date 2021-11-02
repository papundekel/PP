#pragma once
#include "../macros/CIA.hpp"
#include "../utility/forward.hpp"

namespace PP::pack
{
PP_CIA combinator_or_l = [](auto&&... f) -> decltype(auto)
{
    return (false || ... || PP_F(f)());
};
}

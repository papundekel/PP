#pragma once
#include "../macros/CIA.hpp"
#include "../utility/forward.hpp"

namespace PP::pack
{
PP_CIA combinator_and_l = [](auto&&... f) -> decltype(auto)
{
    return (true && ... && PP_F(f)());
};
}

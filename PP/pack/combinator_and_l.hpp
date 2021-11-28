#pragma once
#include <PP/macros/CIA.hpp>
#include <PP/utility/forward.hpp>

namespace PP::pack
{
PP_CIA combinator_and_l = [](auto&&... f) -> decltype(auto)
{
    return (true && ... && PP_F(f)());
};
}

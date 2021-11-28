#pragma once
#include <PP/macros/CIA.hpp>
#include <PP/utility/forward.hpp>

namespace PP::pack
{
PP_CIA combinator_or_l = [](auto&&... f) -> decltype(auto)
{
    return (false || ... || PP_F(f)());
};
}

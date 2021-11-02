#pragma once
#include "../macros/CIA.hpp"
#include "../utility/forward.hpp"

namespace PP::pack
{
PP_CIA map = [](auto&& packer, auto&& f, auto&&... elements) -> decltype(auto)
{
    return PP_F(packer)(PP_F(f)(PP_F(elements))...);
};
}

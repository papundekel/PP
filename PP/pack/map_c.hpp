#pragma once
#include "../forward_wrap.hpp"
#include "../macros/CIA.hpp"
#include "../utility/forward.hpp"

namespace PP::pack
{
// map_c(packer, f)(e...) = packer(f(e)...)
PP_CIA map_c = [](auto&& packer, auto&& f)
{
    return [PP_FL(packer), PP_FL(f)](auto&&... elements) -> decltype(auto)
    {
        return backward(packer)(backward(f)(PP_F(elements))...);
    };
};
}

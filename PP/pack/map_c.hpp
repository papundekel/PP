#pragma once
#include "../macros/CIA.hpp"
#include "../utility/forward.hpp"
#include "../forward_wrap.hpp"

namespace PP::pack
{
// map_c(packer, f)(e...) = packer(f(e)...)
PP_CIA map_c = [](auto&& packer, auto&& f)
{ 
    return [PP_FL(packer), PP_FL(f)](auto&&... elements)-> decltype(auto)
    {
        return unforward(packer)(unforward(f)(PP_F(elements))...);
    };
};
}

#pragma once
#include "../combine_c.hpp"
#include "../forward_wrap.hpp"

namespace PP::pack
{
PP_CIA combinator_f_c = [](auto&& c)
{
    return [PP_FL(c)](auto&&... f) -> decltype(auto)
    {
        return backward(c)(backward(f)()...);
    };
};
}

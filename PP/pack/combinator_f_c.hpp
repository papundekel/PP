#pragma once
#include <PP/forward_wrap.hpp>
#include <PP/macros/CIA.hpp>

namespace PP::pack
{
PP_CIA combinator_f_c = [](auto&& c)
{
    return [PP_FL(c)](auto&&... f) -> decltype(auto)
    {
        return backward(c)(PP_F(f)()...);
    };
};
}

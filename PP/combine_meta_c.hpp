#pragma once
#include "partial_c.hpp"

namespace PP
{
// combine_meta_c(c1)(f...)(a...) = c2(f(a...)...), where c2(g()...) = c1(g...)
PP_CIA combine_meta_c = [](auto&& c)
{
    return [PP_FL(c)](auto&&... f)
    {
        return [PP_UL(c), ... PP_FL(f)](auto&&... args) -> decltype(auto)
        {
            return unforward(c)(
                partial_first_c(make_fw_d(value_2, f))(PP_FW(args)...)...);
        };
    };
};
}

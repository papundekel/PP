#pragma once
#include "macros/CIA.hpp"
#include "utility/forward.hpp"

namespace PP
{
PP_CIA id_forward = [](auto&& x) -> auto&&
{
    return PP_F(x);
};

PP_CIA id_copy = [](auto&& x)
{
    return x;
};
}

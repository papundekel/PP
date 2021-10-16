#pragma once
#include "utility/forward.hpp"
#include "macros/CIA.hpp"

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

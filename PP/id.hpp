#pragma once
#include "get_type.hpp"

namespace PP
{
PP_CIA id_forward = [](auto&& x) -> decltype(auto)
{
    return PP_F(x);
};

PP_CIA id_copy = [](auto&& x)
{
    return x;
};
}

#pragma once
#include <PP/macros/CIA.hpp>
#include <PP/utility/forward.hpp>

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

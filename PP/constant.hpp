#pragma once
#include "forward_wrap.hpp"
#include "id.hpp"
#include "overloaded.hpp"

namespace PP
{
PP_CIA constant = [](auto&& c)
{
    return [PP_FL(c)](auto&&...) -> decltype(auto)
    {
        return overloaded(backward_pure, id_copy)(c);
    };
};
}

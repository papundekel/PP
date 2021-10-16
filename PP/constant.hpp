#pragma once
#include "forward_wrap.hpp"
#include "overloaded.hpp"
#include "id.hpp"

namespace PP
{
PP_CIA constant = [](auto&& c)
{
    return [PP_FL(c)](auto&&...) -> decltype(auto)
    {
        return overloaded(unwrap_forward_pure, id_copy)(c);
    };
};
}

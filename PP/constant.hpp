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
        return overloaded(unwrap_forward_wrap_pure,
                          unwrap_forward_wrap_wrap_pure,
                          id_copy)(c);
    };
};
}

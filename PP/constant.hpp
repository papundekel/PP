#pragma once
#include <PP/forward_wrap.hpp>
#include <PP/id.hpp>
#include <PP/overloaded.hpp>

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

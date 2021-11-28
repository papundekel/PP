#pragma once
#include <PP/utility/move.hpp>

namespace PP
{
PP_CIA move_assign = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) = move(y);
};
}

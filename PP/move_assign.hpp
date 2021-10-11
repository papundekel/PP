#pragma once
#include "functor.hpp"
#include "utility/move.hpp"

namespace PP
{
namespace functors
{
PP_CIA move_assign = [](auto&& x, auto&& y) -> decltype(auto)
{
    return PP_F(x) = move(y);
};
}
PP_FUNCTOR(move_assign)
}

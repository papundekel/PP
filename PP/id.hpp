#pragma once
#include "functor.hpp"
#include "get_type.hpp"

namespace PP
{
PP_FUNCTOR(id_forward, auto&& x) -> decltype(auto)
{
    return PP_F(x);
});

PP_FUNCTOR(id_copy, auto&& x)
{
    return x;
});
}

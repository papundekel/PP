#pragma once
#include "partial_c.hpp"
#include "tuple/apply.hpp"

namespace PP
{
PP_CIA applier = partial_first_c(tuple::apply);
}

constexpr auto operator++(auto&& f, int)
{
    return PP::applier(PP_F(f));
}

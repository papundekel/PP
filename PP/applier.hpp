#pragma once
#include "partial_.hpp"
#include "tuple/apply.hpp"

namespace PP
{
PP_CIA applier = partial_first * tuple::apply;
}

constexpr auto operator++(auto&& f, int)
{
    return PP::applier(PP_F(f));
}

#pragma once
#include "../combine.hpp"
#include "../compose.hpp"
#include "../pack/any.hpp"
#include "../pack/get.hpp"
#include "../partial_.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_CIA all =
    combine(apply, compose(partial_first* pack::any, pack::get_0), pack::get_1);
}

constexpr decltype(auto) operator&&(auto&& f, PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::all(PP_F(f), PP_F(tuple));
}

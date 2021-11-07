#pragma once
#include "../combine.hpp"
#include "../compose.hpp"
#include "../pack/any_c.hpp"
#include "../pack/get.hpp"
#include "../partial_.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_CIA any = combine(apply, compose(pack::any_c, pack::get_0), pack::get_1);
}

constexpr decltype(auto) operator||(auto&& f, PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::any(PP_F(f), PP_F(tuple));
}

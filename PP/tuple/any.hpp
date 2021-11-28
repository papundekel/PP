#pragma once
#include <PP/combine.hpp>
#include <PP/compose.hpp>
#include <PP/pack/any_c.hpp>
#include <PP/pack/get.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/apply.hpp>

namespace PP::tuple
{
PP_CIA any = combine(apply, compose(pack::any_c, pack::get_0), pack::get_1);
}

constexpr decltype(auto) operator||(auto&& f, PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::any(PP_F(f), PP_F(tuple));
}

#pragma once
#include <PP/combine.hpp>
#include <PP/compose.hpp>
#include <PP/pack/all_c.hpp>
#include <PP/pack/get.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/apply.hpp>

namespace PP::tuple
{
PP_CIA all = combine(apply, compose(pack::all_c, pack::get_0), pack::get_1);
}

constexpr decltype(auto) operator&&(auto&& f, PP::concepts::tuple auto&& tuple)
{
    return PP::tuple::all(PP_F(f), PP_F(tuple));
}

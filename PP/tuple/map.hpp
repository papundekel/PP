#pragma once
#include <PP/combine.hpp>
#include <PP/containers/tuple.hpp>
#include <PP/declval.hpp>
#include <PP/forward_wrap.hpp>
#include <PP/operators.hpp>
#include <PP/pack/map_c.hpp>
#include <PP/partial_.hpp>
#include <PP/tuple/apply.hpp>

namespace PP::tuple
{
PP_CIA map_pack = [](auto&& f, auto&&... e)
{
    return pack::map(init, , PP_F(e)...);
};

PP_CIA map =
    combine(apply, compose(partial_first* map_pack, pack::get_0), pack::get_1);
}

constexpr auto operator+(auto&& f, PP::concepts::tuple auto&& t)
{
    return PP::tuple::map(PP_F(f), PP_F(t));
}

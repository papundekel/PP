#pragma once
#include "../combine.hpp"
#include "../containers/tuple.hpp"
#include "../declval.hpp"
#include "../forward_wrap.hpp"
#include "../operators.hpp"
#include "../pack/map.hpp"
#include "../partial_.hpp"
#include "apply.hpp"

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

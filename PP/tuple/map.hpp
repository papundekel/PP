#pragma once
#include "../apply_partially_first.hpp"
#include "../combine.hpp"
#include "../containers/tuple.hpp"
#include "../declval.hpp"
#include "../forward_wrap.hpp"
#include "../functor.hpp"
#include "../functor_or_wrap.hpp"
#include "../operators.hpp"
#include "apply.hpp"

namespace PP::tuple
{
namespace functors
{
PP_CIA map_pack = [](auto&& map, auto&&... elements)
{
    return init((cal * map * PP_FW(elements))...);
};
}
PP_FUNCTOR(map_pack)

PP_CIA map = combine(apply, apply_partially_first * map_pack | get_0, get_1);
}

constexpr auto operator+(PP::concepts::functor_or_wrap auto&& f,
                         PP::concepts::tuple auto&& t)
{
    return PP::tuple::map(PP_F(f), PP_F(t));
}

#pragma once
#include "../apply_partially_first.hpp"
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
PP_CIA map = [](auto&& map, concepts::tuple auto&& t)
{
    return apply(
        [m = PP_FW(map)](auto&&... elements)
        {
            return init((cal * m * PP_FW(elements))...);
        },
        PP_F(t));
};
}
PP_FUNCTOR(map)
}

constexpr auto operator+(PP::concepts::functor_or_wrap auto&& f,
                         PP::concepts::tuple auto&& t)
{
    return PP::tuple::map(PP_F(f), PP_F(t));
}

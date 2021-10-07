#pragma once
#include "../apply_partially_first.hpp"
#include "../containers/tuple.hpp"
#include "../declval.hpp"
#include "../forward_wrap.hpp"
#include "../functor.hpp"
#include "../operators.hpp"
#include "../wrap.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_FUNCTOR(map, auto&& map, concepts::tuple auto&& t)
{
    return apply(
        [m = PP_FW(map)](auto&&... elements)
        {
            return init((cal * m * PP_FW(elements))...);
        },
        PP_F(t));
});
}

constexpr auto operator+(PP::concepts::wrap auto&& f,
                         PP::concepts::tuple auto&& t)
{
    return PP::tuple::map(PP_UF(f), PP_F(t));
}

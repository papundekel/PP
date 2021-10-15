#pragma once
#include "../apply_partially_first.hpp"
#include "../combine.hpp"
#include "../constant.hpp"
#include "../forward_wrap.hpp"
#include "../macros/CIA.hpp"
#include "../utility/move.hpp"
#include "apply.hpp"

namespace PP::detail
{
template <typename F, typename I>
struct fold_wrapper
{
    F&& f;
    I i;
};
template <typename F, typename I>
fold_wrapper(F&&, I) -> fold_wrapper<F, I>;

constexpr auto fold_combinator(concepts::value auto left,
                               auto& wrap,
                               auto&& element)
{
    return fold_wrapper{
        PP_F(wrap.f),
        [f = PP_FW(wrap.f), i = wrap.i, PP_FWL(element)]() -> decltype(auto)
        {
            if constexpr (*PP_CV(left))
                return f(i(), element--);
            else
                return f(element--, i());
        }};
}

template <typename F, typename T>
constexpr auto operator||(fold_wrapper<F, T> wrap, auto&& element)
{
    return fold_combinator(value_true, wrap, PP_F(element));
}
template <typename F, typename T>
constexpr auto operator||(auto&& element, fold_wrapper<F, T> wrap)
{
    return fold_combinator(value_false, wrap, PP_F(element));
}
}

namespace PP::tuple
{
PP_CIA fold_init_pack =
    [](concepts::value auto&& left, auto&& f, auto&& i, auto&&... e)
{
    return [&left, ... PP_FWL(e)](auto wrapper)
    {
        if constexpr (PP_GV(left))
            return (wrapper() || ... || e--);
        else
            return (e-- || ... || wrapper());
    }(
               [PP_FWL(f), PP_FWL(i)]
               {
                   return detail::fold_wrapper{f--, i};
               })
        .i();
};

PP_CIA fold_init = combine(
    apply,
    [](concepts::value auto&& left,
       auto&& ff,
       auto&& ii,
       concepts::tuple auto&&)
    {
        return apply_partially_first(fold_init_pack,
                                     PP_FW(left),
                                     PP_FW(ff),
                                     PP_FW(ii));
    },
    get_3);

PP_CIA fold = combine(fold_init,
                      get_0,
                      get_1,
                      compose(compose(constant, wrap_forward), get_2),
                      get_3);

PP_CIA foldl = fold * value_true;
PP_CIA foldr = fold * value_false;
}

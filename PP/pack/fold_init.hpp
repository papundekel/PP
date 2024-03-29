#pragma once
#include <PP/forward_wrap.hpp>
#include <PP/get_value.hpp>
#include <PP/macros/CIA.hpp>

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

constexpr auto fold_combinator(concepts::value auto&& left,
                               auto& wrap,
                               auto&& element)
{
    return fold_wrapper{
        PP_F(wrap.f),
        [f = PP_FW(wrap.f), i = wrap.i, PP_FWL(element)]() -> decltype(auto)
        {
            if constexpr (*PP_CV(left))
                return f--(i(), element--);
            else
                return f--(element--, i());
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

namespace PP::pack
{
// fold_init(value_true , f, i)(e#0 ... e#n) = f(...f(i(), e#0), ...), e#n)
// fold_init(value_false, f, i)(e#0 ... e#n) = f(e#0, ... f(e#n, i()) ... )
PP_CIA fold_init = [](concepts::value auto&& left, auto&& f, auto&& i)
{
    return [PP_FL(left), PP_FL(f), PP_FL(i)](auto&&... e) -> decltype(auto)
    {
        return [left = forward(left), ... PP_FWL(e)](auto wrapper)
        {
            if constexpr (PP_GV(left--))
                return (wrapper() || ... || e--);
            else
                return (e-- || ... || wrapper());
        }(
                   [f = forward(f), i = forward(i)]
                   {
                       return detail::fold_wrapper{f--,
                                                   [i]() -> decltype(auto)
                                                   {
                                                       return i--();
                                                   }};
                   })
            .i();
    };
};
}

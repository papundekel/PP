#pragma once
#include "../apply_partially_first.hpp"
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
	    [f = PP_FW(wrap.f), i = wrap.i, e = PP_FW(element)]() -> decltype(auto)
	    {
		    if constexpr (*PP_CV(left))
			    return f--(i(), e--);
		    else
			    return f--(e--, i());
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
PP_FUNCTOR(fold_init,
           concepts::value auto left,
           auto&& ff,
           auto&& ii,
           concepts::tuple auto&& tuple)
{
	return apply(
	    [left, f = PP_FW(ff), i = PP_FW(ii)](auto&&... e) -> decltype(auto)
	    {
		    if constexpr (PP_GV(left))
			    return (detail::fold_wrapper{f--, i} || ... || PP_F(e)).i();
		    else
			    return (PP_F(e) || ... || detail::fold_wrapper{f--, i}).i();
	    },
	    PP_F(tuple));
});

PP_FUNCTOR(fold,
           concepts::value auto left,
           auto&& ff,
           auto&& ii,
           concepts::tuple auto&& tuple)
{
	return fold_init(left, PP_F(ff), constant(PP_FW(ii)), PP_F(tuple));
});

PP_CIA foldl = fold * value_true;

PP_CIA foldr = fold * value_false;
}

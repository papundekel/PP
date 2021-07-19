#pragma once
#include "apply_partially_first.hpp"
#include "forward_as.hpp"
#include "forward_wrap.hpp"
#include "tuple_apply.hpp"
#include "utility/move.hpp"

namespace PP
{
	namespace detail
	{
		template <typename F, typename I>
		struct fold_wrapper
		{
			F&& f;
			I i;
		};
		template <typename F, typename I>
		fold_wrapper(F&&, I) -> fold_wrapper<F, I>;

		template <typename F, typename T>
		constexpr auto operator||(fold_wrapper<F, T> wrap, auto&& element)
		{
			return fold_wrapper{
				PP_F(wrap.f),
				[f = PP_FORWARD_WRAP(wrap.f),
			     i = wrap.i,
			     e = PP_FORWARD_WRAP(element)]() -> decltype(auto)
				{
					return f--(i(), e--);
				}};
		}
		template <typename F, typename T>
		constexpr auto operator||(auto&& element, fold_wrapper<F, T> wrap)
		{
			return fold_wrapper{
				PP_F(wrap.f),
				[f = PP_FORWARD_WRAP(wrap.f),
			     i = wrap.i,
			     e = PP_FORWARD_WRAP(element)]() -> decltype(auto)
				{
					return f--(e--, i());
				}};
		}
	}

	PP_FUNCTOR(tuple_fold,
	           concepts::value auto left,
	           auto&& ff,
	           auto&& ii,
	           concepts::tuple auto&& tuple)
	{
		return functor(
			[left,
		     f = forward_wrap(unwrap_functor(PP_F(ff))),
		     i = forward_wrap(unwrap_functor(PP_F(ii)))](
				auto&&... elements) -> decltype(auto)
			{
				if constexpr (PP_GET_VALUE(left))
					return (detail::fold_wrapper{f--, i} || ... ||
				            PP_F(elements))
				        .i();
				else
					return (PP_F(elements) || ... ||
				            detail::fold_wrapper{f--, i})
				        .i();
			})[PP_F(tuple)];
	});

	constexpr inline auto tuple_foldl = tuple_fold * value_true;
	constexpr inline auto tuple_foldr = tuple_fold * value_false;
}

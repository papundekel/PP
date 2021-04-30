#pragma once
#include "forward_as.hpp"
#include "forward_wrap.hpp"
#include "functional/apply_partially_first.hpp"
#include "tuple_apply.hpp"
#include "utility/move.hpp"

namespace PP
{
	namespace detail
	{
		template <typename F, typename T>
		struct fold_wrapper
		{
			F f;
			T init;
		};

#define PP_FORWARD_AS_FOLD_WRAPPER(f, init)                                    \
	::PP::detail::fold_wrapper<decltype(f), decltype(init)>                    \
	{                                                                          \
		f, init                                                                \
	}

		template <typename F, typename T>
		constexpr auto operator||(fold_wrapper<F, T> wrap, auto&& element)
		{
			return PP_FORWARD_AS_FOLD_WRAPPER(
				PP_FORWARD(wrap.f),
				PP_FORWARD(wrap.f)(PP_FORWARD(wrap.init), PP_FORWARD(element)));
		}
		template <typename F, typename T>
		constexpr auto operator||(auto&& element, fold_wrapper<F, T> wrap)
		{
			return PP_FORWARD_AS_FOLD_WRAPPER(
				PP_FORWARD(wrap.f),
				PP_FORWARD(wrap.f)(PP_FORWARD(element), PP_FORWARD(wrap.init)));
		}
	}

	PP_FUNCTOR(tuple_fold,
			   concepts::value auto	  left,
			   auto&&				  f,
			   auto&&				  init,
			   concepts::tuple auto&& tuple)
	{
		return functor(
			[left,
			 f_wrap = PP_FORWARD_WRAP(f),
			 init_wrap =
				 PP_FORWARD_WRAP(init)](auto&&... elements) -> decltype(auto)
			{
				if constexpr (PP_GET_VALUE(left))
					return (PP_FORWARD_AS_FOLD_WRAPPER(
								unwrap_functor(f_wrap.unwrap()),
								init_wrap.unwrap()) ||
							... || PP_FORWARD(elements))
						.init;
				else
					return (PP_FORWARD(elements) || ... ||
							PP_FORWARD_AS_FOLD_WRAPPER(
								unwrap_functor(f_wrap.unwrap()),
								init_wrap.unwrap()))
						.init;
			})[PP_FORWARD(tuple)];
	});

	constexpr inline auto tuple_foldl = tuple_fold * value_true;
	constexpr inline auto tuple_foldr = tuple_fold * value_false;
}

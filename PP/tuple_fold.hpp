#pragma once
#include "tuple_split.hpp"
#include "tuple_apply.hpp"
#include "functional/apply_partially.hpp"

namespace PP
{
	namespace detail
	{
		template <typename F, typename T>
		struct fold_wrapper
		{
			F f;
			T obj;
		};

		#define PP_FOLD_WRAPPER(f, value) (::PP::detail::fold_wrapper<decltype(f), decltype(value)>{ f, value })
		
		template <typename F, typename T, typename U>
		constexpr auto operator||(U&& element, fold_wrapper<F, T> init)
		{
			return PP_FOLD_WRAPPER(PP_FORWARD(init.f), PP_FORWARD(init.f)(PP_FORWARD(element), PP_FORWARD(init.obj)));
		}
		template <typename F, typename T, typename U>
		constexpr auto operator||(fold_wrapper<F, T> init, U&& element)
		{
			return PP_FOLD_WRAPPER(PP_FORWARD(init.f), PP_FORWARD(init.f)(PP_FORWARD(init.obj), PP_FORWARD(element)));
		}
	}

	PP_FUNCTOR(tuple_fold, value_wrap auto left, auto&& f, auto&& init, tuple_like auto&& tuple)
	{
		return tuple_apply(
			[left, &f, &init](auto&&... elements) -> decltype(auto)
			{
				if constexpr (PP_GET_VALUE(left))
					return (PP_FOLD_WRAPPER(PP_FORWARD(f), PP_FORWARD(init)) || ... || PP_FORWARD(elements)).obj;
				else
					return (PP_FORWARD(elements) || ... || PP_FOLD_WRAPPER(PP_FORWARD(f), PP_FORWARD(init))).obj;
			}, PP_FORWARD(tuple));
	}};

	PP_FUNCTOR(tuple_fold1, value_wrap auto left, auto&& f, tuple_like auto&& tuple)
	{
		auto [head, tail] = tuple_split(PP_FORWARD(tuple));
		return tuple_fold(left, PP_FORWARD(f), PP_FORWARD(head), PP_FORWARD(tail));
	}};

	constexpr inline auto tuple_foldl  = tuple_fold (partial_tag, value_true);
	constexpr inline auto tuple_foldr  = tuple_fold (partial_tag, value_false);
	constexpr inline auto tuple_foldl1 = tuple_fold1(partial_tag, value_true);
	constexpr inline auto tuple_foldr1 = tuple_fold1(partial_tag, value_false);
}

#pragma once
#include <utility>
#include "../integer_sequence.hpp"
#include "../tuple.hpp"
#include "../tuple_filter.hpp"
#include "../tuple_find.hpp"
#include "equal.hpp"

namespace PP
{
	namespace detail
	{
		template <auto Count>
		constexpr auto make_sequence(PP::value_t<Count>)
		{
			return std::make_integer_sequence<decltype(Count), Count>{};
		}

		constexpr auto extend_sequence(auto count, auto sequence)
		{
			return tuple_concat(tuple_filter<[s = decltype(sequence){}](auto&& x)
			{
				return !tuple_contains(apply_partially<false>(equal, PP_FORWARD(x)), s);
			}>(make_sequence(count)), sequence);
		}

		constexpr decltype(auto) reorder_element_helper(auto&& args, auto current_index, auto&& applied_indices)
		{
			return get(get(current_index, applied_indices), PP_FORWARD(args));
		}
		template <std::size_t... I>
		constexpr decltype(auto) reorder_helper(auto&& f, auto&& args, auto applied_indices, std::index_sequence<I...>)
		{
			return PP_FORWARD(args), value_v<I>, applied_indices)...);
		}
	}

	template <bool copy, std::size_t... I>
	constexpr inline auto reorder =
		[](auto& f)
		{
			[&f](auto&&... args) -> decltype(auto)
			{
				return detail::reorder_helper
					( f
					, std::forward_as_tuple(args...)
					, detail::extend_sequence(value_v<sizeof...(args)>, std::index_sequence<I...>{})
					, std::make_index_sequence<sizeof...(args)>{});
			};
		};
	template <std::size_t... I>
	constexpr inline auto reorder<true, I...> =
		[](auto&& f)
		{
			[f = PP_FORWARD(f)](auto&&... args) -> decltype(auto)
			{
				return reorder<false, I...>(f)(PP_FORWARD(args)...);
			};
		};
}

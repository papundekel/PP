#pragma once
#include "operators.hpp"
#include "tuple.hpp"
#include "tuple/filter.hpp"
#include "tuple/find_index.hpp"
#include "value_sequence.hpp"

namespace PP
{
namespace detail
{
constexpr auto extend_sequence(auto count, auto sequence)
{
	return tuple_concat(
	    tuple_filter<[s = decltype(sequence){}](auto&& x)
	                 {
		                 return !tuple_contains(
		                     apply_partially<false>(equal, PP_F(x)),
		                     s);
	                 }>(value_sequence_make(count)),
	    sequence);
}

constexpr decltype(auto) reorder_element_helper(auto&& args,
                                                auto current_index,
                                                auto&& applied_indices)
{
	return PP_F(args)[applied_indices[current_index]];
}
template <size_t... I>
constexpr decltype(auto) reorder_helper(auto&& f,
                                        auto&& args,
                                        auto applied_indices,
                                        std::index_sequence<I...>)
{
	        return PP_F(args), value<I>, applied_indices)...);
}
}

template <bool copy, size_t... I>
constexpr inline auto reorder = [](auto& f)
{
	[&f](auto&&... args) -> decltype(auto)
	{
		return detail::reorder_helper(
		    f,
		    std::forward_as_tuple(args...),
		    detail::extend_sequence(value<sizeof...(args)>,
		                            std::index_sequence<I...>{}),
		    std::make_index_sequence<sizeof...(args)>{});
	};
};
template <size_t... I>
constexpr inline auto reorder<true, I...> = [](auto&& f)
{
	[f = PP_F(f)](auto&&... args) -> decltype(auto)
	{
		return reorder<false, I...>(f)(PP_F(args)...);
	};
};
}

#pragma once
#include "tuple.hpp"
#include "tuple_prepend.hpp"
#include "functional/apply_partially.hpp"
#include "overloaded.hpp"

namespace PP
{
	namespace detail
	{
		template <auto filter>
		struct tuple_filter_helper
		{
			constexpr auto operator()() const noexcept
			{
				return std::tuple<>{};
			}
			constexpr auto operator()(auto&& head, auto&&... tail) const noexcept
			{
				auto filtered_tail = (*this)(PP_FORWARD(tail)...);

				if constexpr (filter(std::decay_t<decltype(head)>{}))
					return tuple_prepend(PP_FORWARD(head), filtered_tail);
				else
					return filtered_tail;
			}
		};
	}

	template <auto filter>
	constexpr inline auto tuple_filter = apply_partially<false, true>(tuple_apply, detail::tuple_filter_helper<filter>{});
}

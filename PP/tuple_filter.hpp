#pragma once
#include <tuple>
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
			template <typename Head, typename... Tail>
			constexpr auto operator()(Head&& head, Tail&&... tail) const noexcept
			{
				auto filtered_tail = (*this)(std::forward<Tail>(tail)...);

				if constexpr (filter(std::decay_t<Head>{}))
					return tuple_prepend(std::forward<Head>(head), filtered_tail);
				else
					return filtered_tail;
			}
		};
	}

	template <auto filter>
	constexpr inline auto tuple_filter = apply_partially(tuple_apply, detail::tuple_filter_helper<filter>{});
}

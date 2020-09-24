#pragma once
#include "tuple_split.hpp"

namespace PP
{
	struct tuple_find_default {};

	template <auto predicate, tuple_like Tuple, typename Default = tuple_find_default>
	constexpr auto tuple_find(Tuple tuple, Default d = {}) noexcept
	{
		if constexpr (tuple_size_v<Tuple> != 0)
		{
			auto [head, tail] = tuple_split(tuple);

			if constexpr (predicate(std::remove_reference_t<decltype(head)>{}))
				return head;
			else
				return tuple_find<predicate>(tail, d);
		}
		else
			return d;
	}
}

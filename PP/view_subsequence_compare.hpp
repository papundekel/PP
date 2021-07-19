#pragma once
#include "view_subsequence.hpp"

namespace PP
{
	PP_FUNCTOR(view_subsequence_compare_if,
	           auto&& comparer,
	           concepts::view auto&& a,
	           concepts::view auto&& b)
	{
		auto a_b = view_subsequence_if(PP_F(comparer), PP_F(a), PP_F(b));
		switch (a_b)
		{
			case PP::subsequence_type::proper:
				return std::partial_ordering::less;
			case PP::subsequence_type::equal:
				return std::partial_ordering::equivalent;
			default:
				[[fallthrough]];
			case PP::subsequence_type::none:
				auto b_a =
					view_subsequence_if(PP_F(comparer), PP_F(b), PP_F(a));
				switch (b_a)
				{
					case PP::subsequence_type::proper:
						return std::partial_ordering::greater;
					case PP::subsequence_type::equal:
						[[fallthrough]];
					default:
						[[fallthrough]];
					case PP::subsequence_type::none:
						return std::partial_ordering::unordered;
				}
		}
	});

	constexpr inline auto view_subsequence_compare =
		view_subsequence_compare_if * eql;
}

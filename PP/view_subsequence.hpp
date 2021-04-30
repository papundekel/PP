#pragma once
#include "functional/noop.hpp"
#include "functional/operators.hpp"
#include "view_zip_if.hpp"

namespace PP
{
	enum class subsequence_type
	{
		proper,
		equal,
		none,
	};

	// struct subsequence_type
	//{
	//	int x;
	//	static constexpr subsequence_type proper{0};
	//	static constexpr subsequence_type equal{1};
	//	static constexpr subsequence_type none{2};
	//	constexpr operator std::partial_ordering() const noexcept
	//	{
	//		if (*this == proper)
	//			return
	//	}
	//};

	PP_FUNCTOR(view_subsequence_if,
			   auto&&				 comparer,
			   concepts::view auto&& sub,
			   concepts::view auto&& full)
	{
		bool may_be_proper = false;

		auto [sub_end, full_end] = view_zip_if_pack(
			[&may_be_proper, &comparer](auto&& sub_element, auto&& full_element)
			{
				auto cond = PP_FORWARD(comparer)(PP_FORWARD(sub_element),
												 PP_FORWARD(full_element));

				if (!cond)
					may_be_proper = true;

				return make_tuple(cond, make_array(cond, true));
			},
			noop,
			PP_FORWARD(sub),
			PP_FORWARD(full));

		if (sub_end == view_end(PP_FORWARD(sub)) &&
			full_end == view_end(PP_FORWARD(full)))
		{
			if (may_be_proper)
				return subsequence_type::proper;
			else
				return subsequence_type::equal;
		} else
			return subsequence_type::none;
	});

	constexpr inline auto view_subsequence = view_subsequence_if * eql;
}

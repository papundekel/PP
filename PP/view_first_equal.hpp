#pragma once
#include "functional/applier.hpp"
#include "functional/apply_partially_first.hpp"
#include "functional/negate.hpp"
#include "functional/operators.hpp"
#include "view_find.hpp"
#include "zip_view.hpp"

namespace PP
{
	PP_FUNCTOR(view_first_equal_if,
			   auto&& comparer,
			   concepts::view auto&& a,
			   concepts::view auto&& b)
	{
		return view_find(applier(PP_FORWARD(comparer)),
						 zip_view_pack(PP_FORWARD(a), PP_FORWARD(b)));
	});
	PP_FUNCTOR(view_first_difference_if,
			   auto&& comparer,
			   concepts::view auto&& a,
			   concepts::view auto&& b)
	{
		return view_find(negate(applier(PP_FORWARD(comparer))),
						 zip_view_pack(PP_FORWARD(a), PP_FORWARD(b)));
	});

	constexpr inline auto view_first_equal = view_first_equal_if * eql;
	constexpr inline auto view_first_difference =
		view_first_difference_if * eql;
}

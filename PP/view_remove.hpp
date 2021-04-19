#pragma once
#include "array.hpp"
#include "move_assign.hpp"
#include "simple_view.hpp"
#include "value_t.hpp"
#include "view_zip_if.hpp"

namespace PP
{
	PP_FUNCTOR(view_remove, auto&& predicate, concepts::view auto&& v)
	{
		return view_zip_if_pack([&predicate]
			(auto&&, auto&& element)
			{
				auto cond = !PP_FORWARD(predicate)(PP_FORWARD(element));
				return make_tuple(cond, make_array(cond, true));
			}, move_assign, PP_FORWARD(v), PP_FORWARD(v))[value_0];
	});

	PP_FUNCTOR(view_remove_view, auto&& predicate, concepts::view auto&& v)
	{
		return simple_view(view_begin(PP_FORWARD(v)), view_remove(PP_FORWARD(predicate), PP_FORWARD(v)));
	});
}

#pragma once
#include "array.hpp"
#include "move_assign.hpp"
#include "simple_view.hpp"
#include "value_t.hpp"
#include "view/zip_if.hpp"

namespace PP
{
PP_FUNCTOR(view_remove, auto&& predicate, concepts::view auto&& v)
{
	return view_zip_if_pack(
	    [&predicate](auto&&, auto&& element)
	    {
		    auto cond = !PP_F(predicate)(PP_F(element));
		    return make_tuple(cond, make_array(cond, true));
	    },
	    move_assign,
	    PP_F(v),
	    PP_F(v))[value_0];
});

PP_FUNCTOR(view_remove_view, auto&& predicate, concepts::view auto&& v)
{
	return simple_view(view::begin(PP_F(v)),
	                   view_remove(PP_F(predicate), PP_F(v)));
});
}

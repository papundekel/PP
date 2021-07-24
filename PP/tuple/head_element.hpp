#pragma once
#include "../functor.hpp"

namespace PP::detail
{
constexpr auto tuple_head_element_member(auto&& t) requires requires
{
	{
		PP_F(t).head_element()
		} -> concepts::type;
}
{
	return PP_F(t).head_element();
}
constexpr auto tuple_head_element_nonmember(auto&& t) requires requires
{
	{
		head_element_implementation(PP_F(t))
		} -> concepts::type;
}
{
	return head_element_implementation(PP_F(t));
}

namespace PP::tuple
{
PP_FUNCTOR(head_element, auto&& t)
requires requires
{
	detail::tuple_head_element_member(PP_F(t));
} || requires
{
	detail::tuple_head_element_nonmember(PP_F(t));
}
{
	if constexpr (requires
	              {
		              detail::tuple_head_element_member(PP_F(t));
	              })
		return detail::tuple_head_element_member(PP_F(t));
	else
		return detail::tuple_head_element_nonmember(PP_F(t));
});
}

#pragma once
#include "copy_cv.hpp"
#include "decl_type.hpp"
#include "declval.hpp"
#include "functor.hpp"
#include "get_value.hpp"
#include "tuple_head_element.hpp"
#include "tuple_recursive.hpp"

namespace PP
{
	namespace detail
	{
		template <typename I, typename T>
		concept tuple_concept_element_member = requires
		{
			{
				::PP::declval(::PP::type<T>)
					.element(::PP::declval(::PP::type<I>))
				} -> concepts::type;
		};
		template <typename I, typename T>
		concept tuple_concept_element_nonmember =
			tuple_concept_element_member<I, T> || requires
		{
			{
				element_implementation(::PP::declval(::PP::type<I>),
									   ::PP::declval(::PP::type<T>))
				} -> concepts::type;
		};
		template <typename I, typename T>
		concept tuple_concept_element_recursive =
			tuple_concept_element_nonmember<I, T> || requires
		{
			{
				tuple_recursive(tuple_head_element,
								::PP::declval(::PP::type<I>),
								::PP::declval(::PP::type<T>))
				} -> concepts::type;
		};

		constexpr auto tuple_element_helper(concepts::value auto i,
											auto&& t) requires
			tuple_concept_element_member<decltype(i), decltype(t)>
		{
			return PP_FORWARD(t).element(i);
		}
		constexpr auto tuple_element_helper(concepts::value auto i,
											auto&& t) requires
			tuple_concept_element_nonmember<decltype(i), decltype(t)>
		{
			return element_implementation(i, PP_FORWARD(t));
		}
		constexpr auto tuple_element_helper(concepts::value auto i,
											auto&& t) requires
			tuple_concept_element_recursive<decltype(i), decltype(t)>
		{
			return tuple_recursive(tuple_head_element, i, PP_FORWARD(t));
		}
	}

	PP_FUNCTOR(tuple_element, concepts::value auto i, auto&& t)
	requires detail::tuple_concept_element_recursive<decltype(i), decltype(t)>
	{
		return copy_cv(PP_DECLTYPE(t),
					   detail::tuple_element_helper(i, PP_FORWARD(t)));
	});

	PP_FUNCTOR(tuple_type_element,
			   concepts::value auto i,
			   concepts::type auto t)
	{
		return PP_COPY_TYPE(tuple_element(i, declval(t)));
	});
}

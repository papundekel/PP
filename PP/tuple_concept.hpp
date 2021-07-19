#pragma once
#include "declval.hpp"
#include "get_type.hpp"
#include "macros/simple_concept.hpp"
#include "tuple_count.hpp"
#include "tuple_element.hpp"
#include "tuple_get.hpp"
#include "tuple_value_sequence_for.hpp"
#include "value_t.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T, auto I>
		concept tuple_access = requires
		{
			::PP::declval_impl<T>()[::PP::value<I>];
			::PP::tuple_element(::PP::value<I>, ::PP::declval_impl<T>());
		};
		template <typename T, auto... I>
		concept tuple_accesses = (tuple_access<T, I> && ...);

		template <auto... I>
		constexpr auto is_tuple_helper(concepts::type auto&& t,
		                               value_sequence<I...>) noexcept
		{
			return tuple_accesses<PP_GT(t), I...>;
		}
	}

	// PP_FUNCTOR(is_tuple, concepts::type auto t)
	//{
	//	return requires
	//	{
	//		::PP::tuple_count_value_t(::PP::declval(t));
	//		::PP::detail::is_tuple_helper(
	//			::PP::declval(t),
	//			::PP::tuple_value_sequence_for(::PP::declval(t)));
	//	};
	//});

	namespace concepts
	{
		template <typename T>
		concept tuple = requires
		{
			::PP::tuple_count_value_t(::PP::declval_impl<T>());
		}
		&&PP::detail::is_tuple_helper(
			PP::type<T>,
			tuple_type_value_sequence_for(PP::type<T>));
	}
}

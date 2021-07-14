#pragma once
#include "PP/compose.hpp"
#include "PP/construct_pack.hpp"
#include "PP/decl_type.hpp"
#include "PP/overloaded.hpp"
#include "PP/tuple_make.hpp"
#include "PP/tuple_prepend.hpp"
#include "PP/type_tuple.hpp"

namespace PP
{
	namespace detail
	{
		constexpr auto promotion_type_convertor(int x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(unsigned int x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(long x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(unsigned long x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(long long x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(unsigned long long x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(double x)
		{
			return x;
		}
		constexpr auto promotion_type_convertor(long double x)
		{
			return x;
		}
	}

	PP_FUNCTOR(has_implicit_conversion_to_arithmetic_type,
			   PP::concepts::type auto t)
	{
		return requires(PP_GET_TYPE(t) x)
		{
			promotion_type_convertor(x);
		};
	});

	constexpr inline auto promotion_type =
		decl_type_copy |
		PP::functor(
			[](auto x)
			{
				return detail::promotion_type_convertor(x);
			}) |
		construct_pack;
}

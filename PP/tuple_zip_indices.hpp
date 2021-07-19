#pragma once
#include "compose_apply.hpp"
#include "generator_tuple.hpp"
#include "tuple.hpp"
#include "tuple_count.hpp"
#include "tuple_zip_with.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_zip_indices, concepts::tuple auto&& t)
	{
		return *functor(
				   [](auto i, auto&& element)
				   {
					   return tuple<decltype(i), decltype(element)>(
						   placeholder,
						   i,
						   PP_F(element));
				   }) +
		       (make_id_tuple(tuple_count_value_t(t)) ^ PP_F(t));
	});
}

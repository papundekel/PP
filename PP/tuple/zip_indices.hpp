#pragma once
#include "../compose_apply.hpp"
#include "../containers/tuple.hpp"
#include "../generator_tuple.hpp"
#include "count.hpp"
#include "zip_with.hpp"

namespace PP::tuple
{
PP_FUNCTOR(zip_indices, concepts::tuple auto&& t)
{
	return *functor(
	           [](auto i, auto&& element)
	           {
		           return container<decltype(i), decltype(element)>(
		               placeholder,
		               i,
		               PP_F(element));
	           }) +
	       (make_id_tuple(count_value_t(t)) ^ PP_F(t));
});
}
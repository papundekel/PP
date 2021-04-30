#pragma once
#include "functional/constant.hpp"
#include "functional/functor.hpp"
#include "functional/operators.hpp"
#include "same.hpp"
#include "tuple.hpp"
#include "tuple_find_index.hpp"
#include "tuple_map_default.hpp"
#include "type_t.hpp"

namespace PP
{
	template <typename Key, typename Value>
	using key_value_pair = tuple<type_t<Key>, type_t<Value>>;

	struct key_not_found
	{};

	constexpr inline functor tuple_get_value_from_key
	{
		[]<typename Default = key_not_found>(concepts::tuple auto&& t,
											 Default				d = {})
		{
			constexpr auto i = tuple_find_index(predicate | tuple_get * value_0,
												PP_FORWARD(t));
			if constexpr (i != tuple_type_size(PP_DECLTYPE(tuple)))
				return PP_FORWARD(t)[value<i>][value_1];
			else
				return d;
		});
	}

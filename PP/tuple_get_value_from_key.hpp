#pragma once
#include <utility>
#include "pair.hpp"
#include "functional/comparisons.hpp"
#include "tuple_find.hpp"
#include "type_t.hpp"
#include "same.hpp"
#include "tuple_map_default.hpp"
#include "functional/constant.hpp"

namespace PP
{
	template <typename Key, typename Value>
	using key_value_pair = std::pair<type_t<Key>, type_t<Value>>;

	struct key_not_found {};

	template <auto predicate, typename Default = key_not_found>
	constexpr auto tuple_get_value_from_key(tuple_like auto&& tuple, Default d = {})
	{
		constexpr std::size_t i = tuple_find_index(predicate | tuple_get(partial_tag, value_v<0>), PP_FORWARD(tuple));
		if constexpr (i != tuple_type_size(PP_DECLTYPE(tuple)))
			return tuple_get(value_v<1>, tuple_get(value_v<i>, PP_FORWARD(tuple)));
		else
			return d;
	}
}

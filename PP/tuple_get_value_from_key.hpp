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
		constexpr std::size_t i = tuple_find_index(predicate || tuple_get<0>, std::forward<decltype(tuple)>(tuple));
		if constexpr (i != tuple_size(tuple_map_default<decltype(tuple)>(constant<>(std::tuple<>{}))))
			return tuple_get<1>(tuple_get<i>(std::forward<decltype(tuple)>(tuple)));
		else
			return d;
	}
}

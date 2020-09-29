#pragma once
#include <utility>
#include "pair.hpp"
#include "functional/equal.hpp"
#include "tuple_find.hpp"
#include "type_t.hpp"
#include "same.hpp"

namespace PP
{
	/*template <typename Key, typename Value>
	using key_value_pair = std::pair<type_t<Key>, type_t<Value>>;

	struct key_not_found {};

	template <auto predicate, typename Tuple, typename Default = key_not_found>
	constexpr auto tuple_get_value_from_key(Tuple tuple, Default d = {})
	{
		auto pair = tuple_find<predicate || tuple_get<0>>(std::move(tuple), std::move(d));
		if constexpr (!same<decltype(pair), Default>)
			return tuple_get<1>(pair);
		else
			return pair;
	}*/
}

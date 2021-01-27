#pragma once
#include <type_traits>
#include "ref_qualifier.hpp"
#include "map_v.hpp"
#include "functional/id.hpp"
#include "tuple_get_value_from_key.hpp"
#include "value_t.hpp"
#include "map_t.hpp"
#include "functional/apply_partially.hpp"

namespace PP
{
	template <ref_qualifier ref>
	constexpr inline auto add_ref = tuple_get_value_from_key<[](auto r) { return r == value<ref>; }>(std::make_tuple(
		std::make_pair(PP::value<ref_qualifier::lvalue>, PP::map_v * PP::Template<std::add_lvalue_reference>),
		std::make_pair(PP::value<ref_qualifier::rvalue>, PP::map_v * PP::Template<std::add_rvalue_reference>)),
		PP::id_forward);

	template <ref_qualifier ref, typename T>
	using add_ref_t = map_t<add_ref<ref>>::template get<T>;
}

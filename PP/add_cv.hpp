#pragma once
#include <type_traits>
#include "cv_qualifier.hpp"
#include "map_v.hpp"
#include "functional/id.hpp"
#include "tuple_get_value_from_key.hpp"
#include "value_t.hpp"
#include "map_t.hpp"

namespace PP
{
	template <cv_qualifier cv>
	constexpr inline auto add_cv = get_value_from_key(value_v<cv>, std::make_tuple(
		std::make_pair(value_v<cv_qualifier::none>, id_weak),
		std::make_pair(value_v<cv_qualifier::Const>, map_v(template_v<std::add_const>)),
		std::make_pair(value_v<cv_qualifier::Volatile>, map_v(template_v<std::add_volatile>))),
		map_v(template_v<std::add_cv>));

	template <cv_qualifier cv, typename T>
	using add_cv_t = map_t<add_cv<cv>>::template get<T>;
}

#pragma once
#include "cv_qualifier.hpp"
#include "decompose_pair.hpp"
#include "functional/compose.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline auto decompose_volatile =
		make_overloaded_pack(
			[]<typename T>(type_t<volatile T>)
			{
				return make_decompose_pair(type<T>,
										   PP::value<cv_qualifier::Volatile>);
			},
			[]<typename T>(type_t<T>)
			{
				return make_decompose_pair(type<T>,
										   PP::value<cv_qualifier::none>);
			}) |
		to_type_t;
}

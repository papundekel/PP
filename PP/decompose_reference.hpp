#pragma once
#include "functional/compose.hpp"
#include "decompose_pair.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "ref_qualifier.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline auto decompose_reference = make_overloaded_pack
	(
		[]<typename T>(type_t<T&&>) { return make_decompose_pair(type<T>, PP::value<ref_qualifier::rvalue>); },
		[]<typename T>(type_t<T& >) { return make_decompose_pair(type<T>, PP::value<ref_qualifier::lvalue>); },
		[]<typename T>(type_t<T  >)	{ return make_decompose_pair(type<T>, PP::value<ref_qualifier::none  >); }
	) | to_type_t;
}

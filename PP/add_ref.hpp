#pragma once
#include <type_traits>
#include "ref_qualifier.hpp"
#include "map_v.hpp"
#include "functional/id.hpp"
#include "get_value_from_key.hpp"
#include "value_t.hpp"
#include "map_t.hpp"

namespace PP
{
	template <ref_qualifier ref>
	constexpr inline auto add_ref = get_value_from_key(value_v<ref>, std::make_tuple(
		std::make_pair(value_v<ref_qualifier::lvalue>, map_v<template_v<std::add_lvalue_reference>>),
		std::make_pair(value_v<ref_qualifier::rvalue>, map_v< template_v<std::add_rvalue_reference>>)),
		id_weak);

	template <ref_qualifier ref, typename T>
	using add_ref_t = map_t<add_ref<ref>>::template get<T>;
}

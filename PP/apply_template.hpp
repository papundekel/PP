#pragma once
#include "functional/functor.hpp"
#include "functional/apply_partially.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "template_t.hpp"
#include "tuple_apply.hpp"
#include "tuple_get.hpp"
#include "tuple_like.hpp"
#include "tuple_value_sequence_for.hpp"
#include "type_t.hpp"
#include "value_t.hpp"

namespace PP
{
	constexpr inline functor apply_template_pack{ []
	<template <typename...> typename Template>
	(template_t<Template>, concepts::type auto... types)
	{
		return type<Template<PP_GET_TYPE(types)...>>;
	}};

	PP_FUNCTOR(apply_template, auto Template, concepts::tuple auto&& types)
	{
		return (apply_template_pack * Template)[PP_FORWARD(types)];
	}};

	constexpr inline auto apply_template_type = get_type | apply_template;
	constexpr inline auto apply_template_value = get_type_value | apply_template;

	template <template <typename...> typename Template>
	constexpr auto template_t<Template>::operator[](auto&& types) const noexcept
	{
		return apply_template(*this, PP_FORWARD(types));
	}
	template <template <typename...> typename Template>
	constexpr auto template_t<Template>::operator()(auto... types) const noexcept
	{
		return apply_template_pack(*this, types...);
	}
}

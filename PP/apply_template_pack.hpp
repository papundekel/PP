#pragma once
#include "functor.hpp"
#include "get_type.hpp"
#include "get_value.hpp"
#include "template_t.hpp"
#include "type_t.hpp"

namespace PP
{
	constexpr inline functor apply_template_pack(
		[]<template <typename...> typename Template>(
			template_t<Template>,
			concepts::type auto... types)
		{
			return type<Template<PP_GET_TYPE(types)...>>;
		});

	template <template <typename...> typename Template>
	constexpr auto template_t<Template>::operator()(
		auto... types) const noexcept
	{
		return apply_template_pack(*this, types...);
	}
}
